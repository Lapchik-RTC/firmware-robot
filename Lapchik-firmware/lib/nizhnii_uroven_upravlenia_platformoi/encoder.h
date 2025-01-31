#pragma once
#include <Arduino.h>
#include "HardwareSerial.h"
#include "SLOVAR.h"



struct EncoderParams
{ 
public:
  uint16_t enc_pin_a;       // пин энкодера
  uint16_t enc_pin_b;       // пин энкодера
  int8_t enc_dir;         // условный указатель задавания положительного направления вращения вала двигателя, то есть +-1
  float ppr;
  float tick_to_rad;        // коэф. пересчёта для энкодера на данном моторе
  uint8_t (*get_AB)(void);  // ссылка на метод для обработки соответствующей пары битов порта
};

class Encoder {
  private:
  EncoderParams encoderParams;
  int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива

  
public:
  int16_t counter;         // значение, на которое изменилось положение вала двигателя за 1 итерацию
  uint16_t enc_old;         // хранит значение энкодера в предыдущей итерации(в предыдущем тике)
  float phi;                // угол поворота вала в радианах в данный момент
  float tick;               // угол поворота вала в тиках в данный момент
  float tickOld = 0; 
  float w_moment_rad;       // текущая скорость в рад/c
  float w_moment_tick;      // текущая скорость в тики/c
  //uint16_t ppr;

  Encoder(EncoderParams encoderParams){
    this->encoderParams = encoderParams; 
    this->counter = 0;
    this->enc_old = 0;
    this->phi = 0;
    this->tick = 0;
    this->w_moment_rad = 0;
    this->w_moment_tick = 0;

    encoder_init();
  }
  ////////////////////////////////////////////////////////////////
  void encZero(){tick = 0;}
  ////////////////////////////////////////////////////////////////
  void encoder_init() {
    noInterrupts(); // приостанавливаем прерывания
    // Инициализация пинов энкодера
    pinMode(encoderParams.enc_pin_a, INPUT);
    pinMode(encoderParams.enc_pin_b, INPUT);

    // Настройка прерываний энкодера
    PCICR |= 0b00000101; // включаем прерывание на порту B и D
    PCMSK0 |= 0b11110000; // включаем пины PB4 -- PB7  (PCINT4 -- PCINT7)
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
    
    counter += table[enc_old][enc];
    
    enc_old = enc;
    interrupts();
  }

  float get_phi(){
    return phi;
  }


  /// @brief Функция обновления текущих параметров мотора: скорость, угол
  void enc_tick() {
    
    w_moment_rad = 25.0*2.0 * M_PI * ((counter * 1.0) / encoderParams.ppr);
        
    tick += counter; 
    phi += counter * encoderParams.tick_to_rad;
    
    counter = 0;
  }

  

  float get_tick(){
    return tick;
  }

  float get_w_moment_rad(){
    //enc_tick();
    return w_moment_rad;
  }

  float get_w_moment_tick(){
    return w_moment_tick;
  }
};
