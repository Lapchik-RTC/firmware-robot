#pragma once
#include <Arduino.h>
#include "HardwareSerial.h"
#include "SLOVAR.h"
//#pragma once



struct EncoderParams
{ 
public:
  uint16_t enc_pin_a;       // пин энкодера
  uint16_t enc_pin_b;       // пин энкодера
  uint16_t enc_dir;         // условный указатель задавания положительного направления
  // вращения вала двигателя, то есть +-1
  
  uint8_t (*get_AB)(void);      

  EncoderParams(int a, int b, int dir, int8_t (*get_AB)()): enc_pin_a(a), enc_pin_b(b), enc_dir(dir), get_AB(get_AB) {}
  // EncoderParams(uint16_t enc_pin_a, uint16_t enc_pin_b, uint16_t enc_dir){
  //   this->enc_pin_a = enc_pin_a;
  //   this->enc_pin_b = enc_pin_b;
  //   this->enc_dir = enc_dir;
  // }

      
};

class Encoder {
  private:
  EncoderParams encoderParams;
  int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива

  
public:
  uint16_t counter;         // значение, на которое изменилось положение вала двигателя за 1 итерацию
  float phi;                // угол поворота вала в радианах в данный момент
  float tick;               // угол поворота вала в тиках в данный момент
  float w_moment_rad;       // текущая скорость в рад/c
  float w_moment_tick;      // текущая скорость в тики/c


  Encoder(EncoderParams  &encoderParams) : encoderParams(encoderParams) {
    this->encoderParams = encoderParams; 
    this->counter = 0;
    this->phi = 0;
    this->tick = 0;
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
    PCICR |= 0b00000101; // включаем прерывание на порту B и С
    PCMSK0 |= 0b11110000; // включаем пины PB6 -- PB9 (PCINT4 -- PCINT7)
    PCMSK2 |= 0b11111111; // включаем пины (PCINT16 -- PCINT23)

    // Настройка таблицы переходов
    table[0b00][0b10] = encoderParams.enc_dir;
    table[0b10][0b11] = encoderParams.enc_dir;
    table[0b11][0b01] = encoderParams.enc_dir;
    table[0b01][0b00] = encoderParams.enc_dir;

    table[0b00][0b01] = encoderParams.enc_dir;
    table[0b01][0b11] = encoderParams.enc_dir;
    table[0b11][0b10] = encoderParams.enc_dir;
    table[0b10][0b00] = encoderParams.enc_dir;

    interrupts();
  }

  void isr_handler() {
    static uint8_t enc_old = 0; // хранит значение энкодера в предыдущей итерации
    const uint8_t enc = encoderParams.get_AB();
    Serial.print(encoderParams.get_AB());
    counter += table[enc_old][enc];
    enc_old = enc;
  }
  
  void enc_tick()
{
    // noInterrupts();
    uint16_t counter_inc = counter;
    counter = 0;
    // interrupts();

    phi += counter_inc * TICK_TO_RAD; 
    tick += counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO);  
    
    w_moment_rad = (counter_inc * TICK_TO_RAD)/Ts_s_IN_SEC;
    w_moment_tick = (counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO))/Ts_s_IN_SEC;
  }

  float get_phi(){
    return phi;
  }

  float get_tick(){
    return tick;
  }

  float get_w_moment_rad(){
    return w_moment_rad;
  }

  float get_w_moment_tick(){
    return w_moment_tick;
  }
};