#pragma once
#include<Arduino.h>
#include "HardwareSerial.h"
#include "SLOVAR.h"



struct EncoderParams
{ 
  uint16_t enc_pin_a;
  uint16_t enc_pin_b; 
  uint16_t enc_shift;
  uint16_t enc_dir;
  char16_t enc_port;
  uint8_t enc_mask;
  uint16_t vector_number;

  EncoderParams(uint16_t enc_pin_a, uint16_t enc_pin_b, uint16_t enc_shift, uint16_t enc_dir, char16_t enc_port, uint8_t enc_mask, uint16_t vector_number){
    this->enc_pin_a = enc_pin_a;
    this->enc_pin_b = enc_pin_b;
    this->enc_shift = enc_shift;
    this->enc_dir = enc_dir;
    this->enc_port = enc_port;
    this->enc_mask = enc_mask;
    this->vector_number = vector_number;
  }
};

struct MotorParams
{ 
  uint16_t motor_in_1;
  uint16_t motor_in_2; 
  uint16_t motor_pwm;
  uint16_t motor_dir;

  MotorParams(uint16_t motor_in_1, uint16_t motor_in_2, uint16_t motor_pwm, uint16_t motor_dir){
    this->motor_in_1 = motor_in_1;
    this->motor_in_2 = motor_in_2;
    this->motor_pwm = motor_pwm;
    this->motor_dir = motor_dir;
  }
};d

class Encoder : public EncoderParams {
  public:
  EncoderParams encoderParams;
  uint16_t counter;
  float phi;
  float tick;
  float w_moment_rad;
  float w_moment_tick;
  int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива
  
  public:
  Encoder(EncoderParams  *encoderParams) { 
    this->encoderParams = *encoderParams;
    this->counter = 0;
    this->counter = 0;
    this->counter = 0;
    this->w_moment_rad = 0;
    this->w_moment_tick = 0;

    encoder_init();
  }

  void encoder_init() {
    noInterrupts(); // приостанавливаем прерывания
    // Инициализация пинов энкодера
    pinMode(encoderParams.enc_pin_a, INPUT);
    pinMode(encoderParams.enc_pin_b, INPUT);

    // Настройка прерываний энкодера
    PCICR |= 0b00000001; // включаем прерывание на порту B
    PCMSK0 |= 0b00000011; // включаем пины PB2 и PB3 (PCINT0 и PCINT1)

    // Настройка таблицы переходов
    table[0b00][0b10] = encoderParams.enc_dir;
    table[0b10][0b11] = encoderParams.enc_dir;
    table[0b11][0b01] = encoderParams.enc_dir;
    table[0b01][0b00] = encoderParams.enc_dir;

    table[0b00][0b01] = -encoderParams.enc_dir;
    table[0b01][0b11] = -encoderParams.enc_dir;
    table[0b11][0b10] = -encoderParams.enc_dir;
    table[0b10][0b00] = -encoderParams.enc_dir;

    interrupts();
  }

  ISR(_VECTOR(vector_number)) { // Порт
    static uint8_t enc_old = 0; // хранит значение энкодера в предыдущей итерации
    const uint8_t enc = (encoderParams.enc_port & encoderParams.enc_mask) >> encoderParams.enc_shift;
    
    // вот, что происходит в предыдущей строке:
    //   xxxxABxx
    // & 00001100
    //   0000AB00
    // >>2
    //   000000AB
    
    // Serial.print(enc_old);
    // Serial.print("\t");
    // Serial.print(enc);
    // Serial.print("\t");
    // Serial.println(table[enc_old][enc]);

    counter += table[enc_old][enc];
    enc_old = enc;
  }

  void encoder_tick() {
    noInterrupts(); // приостанавливаем прерывания
    const int16_t counter_inc = counter; // запоминаем количество шагов, которое произошло за данную
    // итерацию
    counter = 0;    // обнуляем количество, которое мы получили за данную итерацию
    interrupts(); // возобновляем прерывания

    phi += counter_inc * tick_to_rad; 
    tick += counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO);  
    
    w_moment_rad = phi/Ts_s_IN_SEC;
    w_moment_tick = tick/Ts_s_IN_SEC;
  }
};

class Motor {

};

class Dvigatel {
  
};


volatile int counter = 0; // количество тиков(шагов) энкодера
float tick = 0; // угол поворота вала в тиках в данный момент, который, возможно,
// не будет использоваться
float tick_to_tick = 0; // коэффициент пересчёта в тики
float w_moment_tick = 0;  // текущая скорость в тики/c
float phi = 0; // угол поворота вала в радианах в данный момент, который, возможно,
// не будет использоваться
float w_moment_rad = 0;  // текущая скорость в рад/c
int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива


void tcocol(float w);
float tcocol_rad();
float tcocol_tick();
float tcocol_w_moment_rad();
float tcocol_w_moment_tick();




<<<<<<< HEAD
=======
// работа с двигателем:

#define MOTOR_IN 10    // пин, отвечающий за направление
#define MOTOR_PWM 6//11    // пин ШИМ
#define MOTOR_DIR 1    // что это? зачем?
#define SUPPLY_VOLTAGE 12   // подаваемое напряжение
>>>>>>> 349cd65d4364c43e95193210b24d0ef92a208e7f

void motor_init()
{
  pinMode(MOTOR_IN_1, OUTPUT);
  pinMode(MOTOR_IN_2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
}

void motor_tick(float w)
{
  float wMax = (KOLVO_ENC_TICK * GEAR_RATIO) / 40;
  float u = 0;
  u = SUPPLY_VOLTAGE*constrain((w/wMax), -1.0, 1.0);
  const int16_t pwm = 255.0 * constrain(u / SUPPLY_VOLTAGE, -1.0, 1.0) * MOTOR_DIR;   // MOTOR_DIR?

  if (pwm >= 0)
  {
    digitalWrite(MOTOR_IN_1, HIGH);
    digitalWrite(MOTOR_IN_2, LOW);
    analogWrite(MOTOR_PWM, pwm);
  }
  else
  {
    digitalWrite(MOTOR_IN_1, LOW);
    digitalWrite(MOTOR_IN_2, HIGH);
    analogWrite(MOTOR_PWM, abs(pwm));   // тут подавалось (255 + pwm)
  }
}

void motor_rad(float w)
{
  float wMax = tick_to_rad * 4000;
  float u = 0;
  u = SUPPLY_VOLTAGE*constrain((w/wMax), -1.0, 1.0);
  const int16_t pwm = 255.0 * constrain(u / SUPPLY_VOLTAGE, -1.0, 1.0) * MOTOR_DIR;   // MOTOR_DIR?

  if (pwm >= 0)
  {
    digitalWrite(MOTOR_IN_1, HIGH);
    digitalWrite(MOTOR_IN_2, LOW);
    analogWrite(MOTOR_PWM, pwm);
  }
  else
  {
    digitalWrite(MOTOR_IN_1, LOW);
    digitalWrite(MOTOR_IN_2, HIGH);
    analogWrite(MOTOR_PWM, abs(pwm));   // тут подавалось (255 + pwm)
  }
}