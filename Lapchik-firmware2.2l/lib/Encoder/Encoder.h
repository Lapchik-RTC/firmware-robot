#pragma once
#include <Arduino.h>
#include "HardwareSerial.h"
// #include "SLOVAR.h"


struct EncoderParams
{ 
public:
  uint16_t enc_pin_a;       // пин энкодера
  uint16_t enc_pin_b;       // пин энкодера
  int8_t enc_dir;         // условный указатель задавания положительного направления вращения вала двигателя, то есть +-1
  float ppr;                // тики на оборот
  float tick_to_rad;        // коэф. пересчёта для энкодера на данном моторе
  uint8_t (*get_AB)(void);  // ссылка на метод для обработки соответствующей пары битов порта
  float Ts_sec;             // Период квантования
  float T_sec;              // Постоянная времени фильтра скорости
};

class Encoder {
private:
  EncoderParams encoderParams;
  int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива

  float I = 0;
  
public:
  int16_t counter;         // значение, на которое изменилось положение вала двигателя за 1 итерацию
  uint16_t enc_old;         // хранит значение энкодера в предыдущей итерации(в предыдущем тике)
  float phi;                // угол поворота вала в радианах в данный момент
  float tick;               // угол поворота вала в тиках в данный момент
  float tickOld = 0; 
  float w_moment_rad_s;       // текущая скорость в рад/c
  float w_moment_tick;      // текущая скорость в тики/c

  Encoder(EncoderParams encoderParams);
  
  void encZero();

  void encoder_init();

  void isr_handler();

  float get_phi();


  /// @brief Функция обновления текущих параметров мотора: скорость, угол
  void enc_tick();
  
  float get_tick();

  float get_w_moment_rad();

  float get_w_moment_tick();
};
