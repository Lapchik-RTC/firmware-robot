#pragma once
#include<Arduino.h>
// работа с энкодером:

#define ENC_PIN_A 2
#define ENC_PIN_B 3

#define ENC_PORT PIND
#define ENC_MASK 0b00001100 // удобное для работы с таблицей обозначение положения,
// полученного с датчика холла
#define ENC_SHIFT 2 // const, которая используется для получения двух чисел,
// обозначающих нынешнее положение вала

#define ENC_DIR 1 // условный указатель направления вращения вала двигателя
#define KOLVO_ENC_TICK 48 // количество тиков датчика холла за 1 полный оборот
#define GEAR_RATIO 47   // передаточное отношение редуктора

volatile int counter = 0; // количество тиков(шагов) энкодера
float tick = 0; // угол поворота вала в тиках в данный момент, который, возможно,
// не будет использоваться
float tick_to_tick = 0; // коэффициент пересчёта в тики
float w_tick = 0;  // текущая скорость в тики/c
float phi = 0; // угол поворота вала в радианах в данный момент, который, возможно,
// не будет использоваться
float tick_to_rad = 0;  // коэффициент пересчёта в радианы
float w_rad = 0;  // текущая скорость в рад/c
int8_t table[4][4] = {0}; // создаём таблицу в виде двумерного массива

void tcocol(float w);
float tcocol_rad();
float tcocol_tick();
float tcocol_w_rad();
float tcocol_w_tick();

void encoder_init()
{
  // Инициализация пинов энкодера
  pinMode(ENC_PIN_A, INPUT);
  pinMode(ENC_PIN_B, INPUT);

  // Настройка прерываний энкодера
  PCICR |= 0b00000100; // включаем прерывание на порту D
  PCMSK2 |= 0b00001100; // включаем пины PD2 и PD3 (PCINT18 и PCINT19)

  // Настройка таблицы переходов
  table[0b00][0b10] = ENC_DIR;
  table[0b10][0b11] = ENC_DIR;
  table[0b11][0b01] = ENC_DIR;
  table[0b01][0b00] = ENC_DIR;

  table[0b00][0b01] = -ENC_DIR;
  table[0b01][0b11] = -ENC_DIR;
  table[0b11][0b10] = -ENC_DIR;
  table[0b10][0b00] = -ENC_DIR;

  // Расчет коэффициента пересчета
  tick_to_rad = 2.0 * M_PI / (KOLVO_ENC_TICK * GEAR_RATIO); // будет нужно, если будем использовать угол,
  // а не тики
  tick_to_tick = 1;

  interrupts();
}

ISR(PCINT2_vect) // Порт D (PCINT16 - PCINT23)
{
    static uint8_t enc_old = 0; // хранит значение энкодера в предыдущей итерации
    const uint8_t enc = (ENC_PORT & ENC_MASK) >> ENC_SHIFT;
    // вот, что происходит в предыдущей строке:
    //   xxxxABxx
    // & 00001100
    //   0000AB00
    // >>2
    //   000000AB
    
    counter += table[enc_old][enc];
    enc_old = enc;
}

void encoder_tick()
{
  noInterrupts(); // приостанавливаем прерывания
  const int16_t counter_inc = counter; // запоминаем количество шагов, которое произошло за данную
  // итерацию
  counter = 0;    // обнуляем количество, которое мы получили за данную итерацию
  interrupts(); // возобновляем прерывания

  phi += counter_inc * tick_to_rad; 
  tick += counter_inc * (KOLVO_ENC_TICK * GEAR_RATIO);  
   
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  float t = 1; // я не понимаю, чему должно быть равно это время...
  // типа какая-то константа, но чему она равна???
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  w_rad = phi/t;
  w_tick = tick/t;
}




// работа с двигателем:

#define MOTOR_IN 10    // пин, отвечающий за направление
#define MOTOR_PWM 11    // пин ШИМ
#define MOTOR_DIR 1    // что это? зачем?
#define SUPPLY_VOLTAGE 12   // подаваемое напряжение

void motor_init()
{
  pinMode(MOTOR_IN, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
}

void motor_tick(float w)
{
  float wMax = KOLVO_ENC_TICK * GEAR_RATIO;   // наверное, надо ещё умножить на время,
  // чтобы wMax не была равна просто количеству шагов за 1 полный оборот,
  // но что это за время?
  float u = 0;
  u = SUPPLY_VOLTAGE*constrain((w/wMax), -1.0, 1.0);
  const int16_t pwm = 255.0 * constrain(u / SUPPLY_VOLTAGE, -1.0, 1.0) * MOTOR_DIR;   // зачем MOTOR_DIR?

  if (pwm >= 0)
  {
    digitalWrite(MOTOR_IN, LOW);
    analogWrite(MOTOR_PWM, pwm);
  }
  else
  {
    digitalWrite(MOTOR_IN, HIGH);
    analogWrite(MOTOR_PWM, abs(pwm));   // тут почему-то подавалось (255 + pwm)?
  }
}

void motor_rad(float w)
{
  float wMax = tick_to_rad;   // наверное, надо ещё умножить на время,
  // чтобы wMax не была равна просто количеству радиан за 1 полный оборот,
  // но что это за время?
  float u = 0;
  u = SUPPLY_VOLTAGE*constrain((w/wMax), -1.0, 1.0);
  const int16_t pwm = 255.0 * constrain(u / SUPPLY_VOLTAGE, -1.0, 1.0) * MOTOR_DIR;   // зачем MOTOR_DIR?

  if (pwm >= 0)
  {
    digitalWrite(MOTOR_IN, LOW);
    analogWrite(MOTOR_PWM, pwm);
  }
  else
  {
    digitalWrite(MOTOR_IN, HIGH);
    analogWrite(MOTOR_PWM, abs(pwm));   // тут почему-то подавалось (255 + pwm)?
  }
}

