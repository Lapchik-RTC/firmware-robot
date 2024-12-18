#pragma once
#include<Arduino.h>
#include"tcokol.h"

#define INA 11
#define INB 10
#define PWM 6

#define ENCA 2  // PD0
#define ENCB 4  // PA1
#define ENC_PPR 448
#define ENC_DIR -1
#define MDIR 1

#define KP 0.0001
#define KI 0.00001
#define KE 0.8
#define Ts_s 4000
volatile int32_t enc = 0;

float goalSpeed = 10;

  void motorInit() {
  pinMode(INA, 1);
  pinMode(INB, 1);
  pinMode(PWM, 1);
  pinMode(ENCA, 0);
  pinMode(ENCB, 0);
}
// void motor(int mv) {
//   digitalWrite(INA, mv < 0);
//   digitalWrite(INB, mv > 0);
//   analogWrite(PWM, min(abs(mv), 255));
// }
// void encoder() {
//   // bool dir = digitalRead(ENCA) ^ digitalRead(ENCB);
//   // enc += dir ? ENC_DIR : -ENC_DIR;
//   if (digitalRead(ENCB)) {
//     enc++;
//   } else {
//     enc--;
//   }
// }

float PIreg(float err) {
  static float P, I = 0;
  float maxI = 200;
  P = err * KP;
  I = I + err * KI * Ts_s;
  if (I > maxI) { I = maxI; }
  return P + I;
}

void PIapply(){
    static int realSpeed = 0;
    static int32_t encCounter = 0;
    static int count = 0;
    static int32_t timer = millis();
    timer = millis();
    while (millis() - timer < 10) {
    //Serial.print(" ");
    noInterrupts();
    count = enc;
    enc = 0;
    interrupts();
    encCounter += count;
    }
    realSpeed = 200.0 * M_PI * (encCounter * 1.0 / ENC_PPR); //скорость в радианах в милисекунду
    Serial.print(realSpeed);
    Serial.print('\t');
    Serial.print(encCounter);
    Serial.print('\t');
    Serial.print((millis() - timer));
    //motor(20);
    encCounter = 0;
    //delay(100);
    timer = millis();
/////////////////////////////////////////////////////////////////////
    float u = PIreg(goalSpeed - realSpeed);
    Serial.print('\t');
    Serial.print(goalSpeed - realSpeed);
    Serial.print('\t');
    Serial.println(u);
    motor_tick(u);
}