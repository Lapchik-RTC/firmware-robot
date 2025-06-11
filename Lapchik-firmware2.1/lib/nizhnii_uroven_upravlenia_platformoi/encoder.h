#pragma once
#include <Arduino.h>
#include "HardwareSerial.h"
#include "SLOVAR.h"
#include "f.h"

#define MAX_TICK_CORR 2

struct EncoderParams
{ 
public:
  uint16_t  enc_pin_a;       // пин энкодера
  uint16_t  enc_pin_b;       // пин энкодера
  int8_t    enc_dir;         // условный указатель задавания положительного направления вращения вала двигателя, то есть +-1
  float     ppr;                // тики на оборот
  float     tick_to_rad;        // коэф. пересчёта для энкодера на данном моторе
  uint8_t   (*get_AB)(void);  // ссылка на метод для обработки соответствующей пары битов порта
  float     Ts_sec;             // Период квантования
  float     T_sec;              // Постоянная времени фильтра скорости

  byte      Hpin;
  uint16_t  tickWhanHall;
};

class Encoder
{
private:
  EncoderParams encoderParams;
  int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива

  float I = 0;
  
public:
  volatile int16_t counter;         // значение, на которое изменилось положение вала двигателя за 1 итерацию
  uint16_t enc_old;         // хранит значение энкодера в предыдущей итерации(в предыдущем тике)
  
  float phi;                // угол поворота вала в радианах в данный момент
  float tick;               // угол поворота вала в тиках в данный момент
  
  float w_moment_rad_s;       // текущая скорость в рад/c
  float w_moment_tick;      // текущая скорость в тики/c

  Encoder(EncoderParams encoderParams){
    this->encoderParams = encoderParams; 
    this->counter = 0;
    this->enc_old = 0;
    this->phi = 0;
    this->tick = 0;
    this->w_moment_rad_s = 0;
    this->w_moment_tick = 0;

    encoder_init();
  }

  void encoder_init() {
    noInterrupts(); // приостанавливаем прерывания
    // Инициализация пинов энкодера
    pinMode(encoderParams.enc_pin_a, INPUT);
    pinMode(encoderParams.enc_pin_b, INPUT);

    // Настройка прерываний энкодера
    PCICR |= 0b00000111; // включаем прерывание на порту B и D
    PCMSK0 |= 0b11110000; // включаем пины PB4 -- PB7  (PCINT4 -- PCINT7)
    PCMSK1 |= 0b00000110;
    PCMSK2 |= 0b11111111; // включаем пины (PCINT16 -- PCINT23)

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

  void isr_handler() {
    noInterrupts();
    uint16_t enc = encoderParams.get_AB();
    interrupts();

    counter += table[enc_old][enc];
    enc_old = enc;  
  }
  
  void encZero(){counter = 0; tick = 0; phi = 0; I = 0;}

  float get_phi(){ return phi; }
  float get_mphi(){ return modc(phi, 2.0*M_PI); }
  float get_tick(){ return tick; }
  float get_w_moment_rad(){ return w_moment_rad_s; }
  float get_w_moment_tick(){ return w_moment_tick; }
  float getCorr(){ return corr; }

  /// @brief Функция обновления текущих параметров мотора: скорость, угол

  float rotErr = 0.0;
  float corr = 0.0;
  uint32_t lastTimeDetect = millis();
  void enc_tick() {

    noInterrupts();
    int16_t counter_buf = counter;
    counter = 0;
    interrupts();
    
    ////////////////////////////////////
    if(NCalibrMode)
    {
      if(digitalRead(encoderParams.Hpin) == 0 && ( millis() - lastTimeDetect > (1839) ))
      {
        rotErr += ( encoderParams.tickWhanHall - (modc(tick, encoderParams.ppr)) );
        lastTimeDetect = millis();
      }
      corr = constrain(rotErr, -MAX_TICK_CORR, MAX_TICK_CORR);
      counter_buf += corr;
      rotErr -= corr;
     }
    ////////////////////////////////////
    
    tick += counter_buf; 
    phi += counter_buf * ((2.0*M_PI)/(encoderParams.ppr));
    
    w_moment_rad_s = (phi - I) / encoderParams.T_sec / 3.0;
    I += w_moment_rad_s * encoderParams.Ts_sec;
    Serial.print(w_moment_rad_s);
  }
};
