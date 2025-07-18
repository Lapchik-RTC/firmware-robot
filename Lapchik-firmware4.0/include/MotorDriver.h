#pragma once
#include <Arduino.h>
#include "Parameters.h"
#include "Tau.h"
#include "f.h"
struct MotorDriversSet
{
  float      supply_voltage;    // подаваемое напряжение
  float      Ts;                // Период квантования
  float      T_sec;             // Постоянная времени фильтра скорости
  float      maxU;              // Максимальное напряжение на двигателе
  float      maxAccel;
};

struct MotorConnect
{
  uint8_t    motor_in_1;        // пин, отвечающий за направление
  uint8_t    motor_in_2;        // пин, отвечающий за направление
  uint8_t    motor_pwm;         // пин ШИМ
  uint8_t    enc_pin_a;         // пин энкодера
  uint8_t    enc_pin_b;         // пин энкодера
};

struct MotorParams
{
    int8_t    motor_dir;        // условный указатель для управления направлением  
    int8_t    enc_dir;          // условный указатель задавания положительного направления вращения вала двигателя, то есть +-1
    uint16_t  ppr;              // тики на оборот
    uint8_t   (*get_AB)(void);  // ссылка на метод для обработки соответствующей пары битов порта
    float     p_kp;
    float     kp;
    float     ki;
};


class Motor
{
    private:
    MotorDriversSet *drvSet;
    MotorConnect *mconnp;
    MotorParams *mprm;

    float u = 0.0;
    
    int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива

    FOD spdFilter;
    RateLimiter accLimiter;
    volatile int16_t  counter;         // значение, на которое изменилось положение вала двигателя за 1 итерацию
    uint16_t          enc_old = 0.0;         // хранит значение энкодера в предыдущей итерации(в предыдущем тике)
    float             phi = 0.0;             // угол поворота вала в радианах в данный момент
    int32_t           pulses = 0;            // угол поворота вала в тиках в данный момент 
    float             w_rads = 0.0;          // текущая скорость в рад/c
    
    enum CONTROL_MODE
    {
      MODE_POS,
      MODE_SPEED
    };
    CONTROL_MODE controlMode = MODE_SPEED;

    float targetSpeed = 0.0;
    float targetAngle = 0;

    PIreg piReg;

    public:
    Motor(MotorDriversSet *_drvSet, MotorConnect *_mconnp, MotorParams *_mprm);

    void isr_handler();

    void setU(float _u){ this->u = _u; };
    void setSpeed(float goalSpeed);
    void setPos(float goalAngle);

    float getAngle(){return phi;}
    float getRealSpd(){return w_rads;}
    int32_t getEnc(){return pulses;}

    void tickU();
    void tickEnc();
    void tick();
};

////////////////////////////////////////////////////////////////////
//
////////////////////////   REGULATORI   ////////////////////////////
//
////////////////////////////////////////////////////////////////////
void Motor::setSpeed(float goalSpd)
{
  controlMode = MODE_SPEED;
  targetSpeed = accLimiter.tick(goalSpd);
}

void Motor::setPos(float goalAngle){
  controlMode = MODE_POS;
  targetAngle = goalAngle;
}

void Motor::tick()
{
  tickEnc();
  if(controlMode == MODE_POS)
  {
    float ph0 = modc(phi, 2.0*M_PI);
    float phi_err = targetAngle - ph0; 
    // float phi_err = targetAngle - phi;
    phi_err = modc(phi_err, 2*M_PI);
    
    targetSpeed = phi_err * mprm->p_kp; // P
  }
  setU( piReg.tick(targetSpeed - w_rads) );
  tickU();
}



////////////////////////////////////////////////////////////////////
//
///////////////////////////   ENCODER   ////////////////////////////
//
////////////////////////////////////////////////////////////////////
void Motor::isr_handler() {
  noInterrupts();
  uint16_t enc = mprm->get_AB();
  interrupts();

  counter += table[enc_old][enc];
  enc_old = enc;  
}

void Motor::tickEnc()
{
  noInterrupts();
  int16_t counter_buf = counter;
  counter = 0;
  interrupts();

  pulses += counter_buf; 
  phi += counter_buf * ((2.0*M_PI)/(mprm->ppr));
  w_rads = spdFilter.tick(phi);
}

////////////////////////////////////////////////////////////////////
//
////////////////////////////   MOTOR   /////////////////////////////
//
////////////////////////////////////////////////////////////////////

void Motor::tickU()
{
  int16_t pwm = 255.0 * (u / drvSet->supply_voltage)*1.0;
  digitalWrite(mconnp->motor_in_1, (pwm > 0)*mprm->motor_dir);
  digitalWrite(mconnp->motor_in_2, (!(pwm > 0))*mprm->motor_dir);
  pwm = abs(pwm);
  analogWrite(mconnp->motor_pwm, min( pwm, 255 ));
}

Motor::Motor(MotorDriversSet *_drvSet, MotorConnect *_mconnp, MotorParams *_mprm):
 drvSet(_drvSet),
 mconnp(_mconnp),
 mprm(_mprm),
 spdFilter(drvSet->Ts, drvSet->T_sec, true),
 piReg(drvSet->Ts, mprm->kp, mprm->ki, drvSet->maxU),
 accLimiter(drvSet->Ts, drvSet->maxAccel)
{
  pinMode(mconnp->motor_in_1, 1);
  pinMode(mconnp->motor_in_2, 1);
  pinMode(mconnp->motor_pwm,  1);
  noInterrupts();
  pinMode(mconnp->enc_pin_a, 0);
  pinMode(mconnp->enc_pin_b, 0);
      
  // Настройка прерываний энкодера
  PCICR |= 0b00000111; // включаем прерывание на порту B и D
  PCMSK0 |= 0b11110000; // включаем пины PB4 -- PB7  (PCINT4 -- PCINT7)
  PCMSK1 |= 0b00000110;
  PCMSK2 |= 0b11111111; // включаем пины (PCINT16 -- PCINT23)

  // Настройка таблицы переходов
  table[0b00][0b10] = mprm->enc_dir;
  table[0b10][0b11] = mprm->enc_dir;
  table[0b11][0b01] = mprm->enc_dir;
  table[0b01][0b00] = mprm->enc_dir;

  table[0b00][0b01] = -mprm->enc_dir;
  table[0b01][0b11] = -mprm->enc_dir;
  table[0b11][0b10] = -mprm->enc_dir;
  table[0b10][0b00] = -mprm->enc_dir;
  interrupts();
}