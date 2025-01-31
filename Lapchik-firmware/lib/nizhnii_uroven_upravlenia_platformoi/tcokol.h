// //#pragma once
// #ifndef TCOKOL_H
// #define TCOKOL_H
// #include<Arduino.h>
// #include "HardwareSerial.h"
// #include <SLOVAR.h>



// struct EncoderParams
// { 
// public:
//   uint16_t enc_pin_a;       // пин энкодера
//   uint16_t enc_pin_b;       // пин энкодера
//   uint16_t enc_dir;         // условный указатель задавания положительного направления
//   // вращения вала двигателя, то есть +-1
        
// public:
//   EncoderParams(uint16_t enc_pin_a, uint16_t enc_pin_b, uint16_t enc_dir){
//     this->enc_pin_a = enc_pin_a;
//     this->enc_pin_b = enc_pin_b;
//     this->enc_dir = enc_dir;
//   }
//   uint8_t (*get_AB)();
      
// };

// struct DvigatelParams
// { 
//   uint16_t motor_in_1;        // пин, отвечающий за направление
//   uint16_t motor_in_2;        // пин, отвечающий за направление
//   uint16_t motor_pwm;         // пин ШИМ
//   uint16_t motor_dir;         // условный указатель для управления направлением
//   // вращения вала двигателя, то есть +-1
//   uint16_t supply_voltage;    // подаваемое напряжение

//   DvigatelParams(uint16_t motor_in_1, uint16_t motor_in_2, uint16_t motor_pwm, uint16_t motor_dir, uint16_t supply_voltage){
//     this->motor_in_1 = motor_in_1;
//     this->motor_in_2 = motor_in_2;
//     this->motor_pwm = motor_pwm;
//     this->motor_dir = motor_dir;
//     this->supply_voltage = supply_voltage;
//   }
// };

// class Encoder {
//   private:
//   EncoderParams encoderParams;
//   uint16_t counter;         // значение, на которое изменилось положение вала двигателя за 1 итерацию
//   int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива

  
// public:
//   float phi;                // угол поворота вала в радианах в данный момент
//   float tick;               // угол поворота вала в тиках в данный момент
//   float w_moment_rad;       // текущая скорость в рад/c
//   float w_moment_tick;      // текущая скорость в тики/c


//   Encoder(EncoderParams  *encoderParams) : encoderParams(*encoderParams) {
//     this->encoderParams = *encoderParams; 
//     this->counter = 0;
//     this->phi = 0;
//     this->tick = 0;
//     this->w_moment_rad = 0;
//     this->w_moment_tick = 0;

//     encoder_init();
//   }

//   void encoder_init() {
//     noInterrupts(); // приостанавливаем прерывания
//     // Инициализация пинов энкодера
//     pinMode(encoderParams.enc_pin_a, INPUT);
//     pinMode(encoderParams.enc_pin_b, INPUT);

//     // Настройка прерываний энкодера
//     PCICR |= 0b00000101; // включаем прерывание на порту B и С
//     PCMSK0 |= 0b11110000; // включаем пины PB6 -- PB9 (PCINT4 -- PCINT7)
//     PCMSK2 |= 0b11111111; // включаем пины (PCINT16 -- PCINT23)

//     // Настройка таблицы переходов
//     table[0b00][0b10] = encoderParams.enc_dir;
//     table[0b10][0b11] = encoderParams.enc_dir;
//     table[0b11][0b01] = encoderParams.enc_dir;
//     table[0b01][0b00] = encoderParams.enc_dir;

//     table[0b00][0b01] = -encoderParams.enc_dir;
//     table[0b01][0b11] = -encoderParams.enc_dir;
//     table[0b11][0b10] = -encoderParams.enc_dir;
//     table[0b10][0b00] = -encoderParams.enc_dir;

//     interrupts();
//   }

//   void isr_handler() {
//     static uint8_t enc_old = 0; // хранит значение энкодера в предыдущей итерации
//     const uint8_t enc = encoderParams.get_AB();

//     counter += table[enc_old][enc];
//     enc_old = enc;
//   }
  
//   void enc_tick()
// {
//     noInterrupts();
//     int counter_inc = counter;
//     interrupts();

//     phi += counter_inc * TICK_TO_RAD; 
//     tick += counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO);  
    
//     w_moment_rad = (counter_inc * TICK_TO_RAD)/Ts_s_IN_SEC;
//     w_moment_tick = (counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO))/Ts_s_IN_SEC;
//   }

//   float get_phi(){
//     return phi;
//   }

//   float get_tick(){
//     return tick;
//   }

//   float get_w_moment_rad(){
//     return w_moment_rad;
//   }

//   float get_w_moment_tick(){
//     return w_moment_tick;
//   }
// };

// class Dvigatel {
// private:
//   DvigatelParams dvigatelParams;
  
// public:
//   Dvigatel(DvigatelParams *dvigatelParams) : dvigatelParams(*dvigatelParams) {
//     this->dvigatelParams = *dvigatelParams;
//     dvigatel_init();
//   }
  
  
//   void dvigatel_init() {
//     pinMode(dvigatelParams.motor_in_1, OUTPUT);
//     pinMode(dvigatelParams.motor_in_2, OUTPUT);
//     pinMode(dvigatelParams.motor_pwm,  OUTPUT);
//   }

//   void update_speed_in_tick(float w) {
//     float wMax = (KOLVO_ENC_TICK * GEAR_RATIO) / Ts_s_IN_SEC;
//     float u = 0;
//     u = dvigatelParams.supply_voltage*constrain((w/wMax), -1.0, 1.0);
//     const int16_t pwm = 255.0 * constrain(u / dvigatelParams.supply_voltage, -1.0, 1.0) * dvigatelParams.motor_dir;

//     if (pwm >= 0)
//     {
//       digitalWrite(dvigatelParams.motor_in_1, HIGH);
//       digitalWrite(dvigatelParams.motor_in_2, LOW);
//       analogWrite(dvigatelParams.motor_pwm, pwm);
//     }
//     else
//     {
//       digitalWrite(dvigatelParams.motor_in_1, LOW);
//       digitalWrite(dvigatelParams.motor_in_2, HIGH);
//       analogWrite(dvigatelParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
//     }
//   }

//   void update_voltage_in_V(float w) {
//     float wMax = TICK_TO_RAD / Ts_s_IN_SEC;
//     float u = 0;
//     u = dvigatelParams.supply_voltage*constrain((w/wMax), -1.0, 1.0);
//     const int16_t pwm = 255.0 * constrain(u / dvigatelParams.supply_voltage, -1.0, 1.0) * dvigatelParams.motor_dir;

//     if (pwm >= 0)
//     {
//       digitalWrite(dvigatelParams.motor_in_1, HIGH);
//       digitalWrite(dvigatelParams.motor_in_2, LOW);
//       analogWrite(dvigatelParams.motor_pwm, pwm);
//     }
//     else
//     {
//       digitalWrite(dvigatelParams.motor_in_1, LOW);
//       digitalWrite(dvigatelParams.motor_in_2, HIGH);
//       analogWrite(dvigatelParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
//     }
//   }
// };
// #endif