#pragma once
#include<Arduino.h>
#include "HardwareSerial.h"
#include "SLOVAR.h"



struct EncoderParams
{ 
  uint16_t enc_pin_a;       // пин энкодера
  uint16_t enc_pin_b;       // пин энкодера
  char16_t enc_port;        // порт прерываний
  uint8_t enc_mask;         // удобное для работы с таблицей обозначение положения,
  // полученного с датчика холла
  uint16_t enc_shift;       // const, которая используется для получения двух чисел,
  // обозначающих нынешнее положение вала
  uint16_t enc_dir;         // условный указатель задавания положительного направления
  // вращения вала двигателя, то есть +-1
  uint16_t vector_number;   // номер вектора прерывания

  EncoderParams(uint16_t enc_pin_a, uint16_t enc_pin_b, char16_t enc_port, uint8_t enc_mask, uint16_t enc_shift, uint16_t enc_dir, uint16_t vector_number){
    this->enc_pin_a = enc_pin_a;
    this->enc_pin_b = enc_pin_b;
    this->enc_port = enc_port;
    this->enc_mask = enc_mask;
    this->enc_shift = enc_shift;
    this->enc_dir = enc_dir;


    this->vector_number = vector_number;
  }
};

struct MotorParams
{ 
  uint16_t motor_in_1;        // пин, отвечающий за направление
  uint16_t motor_in_2;        // пин, отвечающий за направление
  uint16_t motor_pwm;         // пин ШИМ
  uint16_t motor_dir;         // условный указатель для управления направлением
  // вращения вала двигателя, то есть +-1
  uint16_t supply_voltage;    // подаваемое напряжение

  MotorParams(uint16_t motor_in_1, uint16_t motor_in_2, uint16_t motor_pwm, uint16_t motor_dir, uint16_t supply_voltage){
    this->motor_in_1 = motor_in_1;
    this->motor_in_2 = motor_in_2;
    this->motor_pwm = motor_pwm;
    this->motor_dir = motor_dir;
    this->supply_voltage = supply_voltage;
  }
};

class Encoder {
  public:
  EncoderParams encoderParams;
  uint16_t counter;         // значение, на которое изменилось положение вала двигателя за 1 итерацию
  float phi;                // угол поворота вала в радианах в данный момент
  float tick;               // угол поворота вала в тиках в данный момент
  float w_moment_rad;       // текущая скорость в рад/c
  float w_moment_tick;      // текущая скорость в тики/c
  int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива
  
  public:
  Encoder(EncoderParams  *encoderParams) { 
    this->encoderParams = *encoderParams;
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

    phi += counter_inc * TICK_TO_RAD; 
    tick += counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO);  
    
    w_moment_rad = (counter_inc * TICK_TO_RAD)/Ts_s_IN_SEC;
    w_moment_tick = (counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO))/Ts_s_IN_SEC;
  }
};

class Motor {
  public:
  MotorParams motorParams;
  uint16_t supply_voltage;
  
  Motor(MotorParams motorParams) {
    this->encoderParams = encoderParams;
    motor_init();
  }
  
  void motor_init() {
    pinMode(motorParams.motor_in_1, OUTPUT);
    pinMode(motorParams.motor_in_2, OUTPUT);
    pinMode(motorParams.motor_pwm,  OUTPUT);
  }

  void motor_speed_tick(float w) {
    float wMax = (KOLVO_ENC_TICK * GEAR_RATIO) / Ts_s_IN_SEC;
    float u = 0;
    u = motorParams.supply_voltage*constrain((w/wMax), -1.0, 1.0);
    const int16_t pwm = 255.0 * constrain(u / motorParams.supply_voltage, -1.0, 1.0) * motorParams.motor_dir;

    if (pwm >= 0)
    {
      digitalWrite(motorParams.motor_in_1, HIGH);
      digitalWrite(motorParams.motor_in_2, LOW);
      analogWrite(motorParams.motor_pwm, pwm);
    }
    else
    {
      digitalWrite(motorParams.motor_in_1, LOW);
      digitalWrite(motorParams.motor_in_2, HIGH);
      analogWrite(motorParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
    }
  }

  void motor_speed_rad(float w) {
    float wMax = TICK_TO_RAD / Ts_s_IN_SEC;
    float u = 0;
    u = motorParams.supply_voltage*constrain((w/wMax), -1.0, 1.0);
    const int16_t pwm = 255.0 * constrain(u / motorParams.supply_voltage, -1.0, 1.0) * motorParams.motor_dir;

    if (pwm >= 0)
    {
      digitalWrite(motorParams.motor_in_1, HIGH);
      digitalWrite(motorParams.motor_in_2, LOW);
      analogWrite(motorParams.motor_pwm, pwm);
    }
    else
    {
      digitalWrite(motorParams.motor_in_1, LOW);
      digitalWrite(motorParams.motor_in_2, HIGH);
      analogWrite(motorParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
    }
  }
};

class Dvigatel {
  public:
  Encoder encoder;
  Motor motor;

  public:
  void update_speed_in_rad(float w);
  void update_speed_in_tick(float w);
  float get_rad();
  float get_tick();
  float get_w_moment_rad();
  float get_w_moment_tick();

  Dvigatel(Encoder encoder, Motor motor) {
    this->encoder = encoder;
    this->motor = motor;

  }

  void update_speed_in_rad(float w) {
    motor.motor_speed_rad(w);
  }

  void update_speed_in_tick(float w) {
    motor.motor_speed_tick(w);
  }

  float get_rad() {
    return encoder.phi;
  }

  float get_tick() {
    return encoder.tick;
  }

  float get_w_moment_rad() {
    return encoder.w_moment_rad;
  }

  float get_w_moment_tick() {
    return encoder.w_moment_tick;
  }
};