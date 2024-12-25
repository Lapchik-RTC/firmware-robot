#include <Arduino.h>
//#include "Poehali.h"
#include "SLOVAR.h"
#include "tcokol.h"
#include "regulatori.h"

// MotorConnectParams mconp = {
//     .INA = 39,
//     .INB = 37,
//     .PWM = 7,
//     .ENCA = 2,
//     .ENCB = 27,
//     .ENC_PPR = 465,
//     .ke = MOTORS_KE,
//     .ENC_DIR = 1
// };
MotorRegulatorParams mcontp = 
{
    .Ts = Ts_s,
    .kp = MOTORS_PI_KP,
    .ki = MOTORS_PI_KI,
    .maxI = MOTORS_PI_MAX_I
};



volatile int value = 0;



void setup(){
    encoder_init();
    motor_init();
  
    pinMode(A1, INPUT);
    pinMode(2, 0);
    pinMode(8, 0);
    // cli();
    // PCICR |= 0b00000101;  // Включить на порту D и B
    // PCMSK0 |= 0b00000001; // Включить пин PB0 (PCINT0), пин 8 на Arduino
    // PCMSK2 |= 0b00000100; // PCINT11
    // sei();
    //attachInterrupt(digitalPinToInterrupt(mconp.ENCA), [](){motor.encoder();}, FALLING);
    Serial.begin(9600);
}
//#define Ts_us 5000 // Период квантования в [мкс]
//#define Ts_s (Ts_us / 1000000.0) // Период квантования в [с]
//обьявленно выше
void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s)
    ;
    timer = micros();
    

}
 




    // Serial.print(digitalRead(2));
    // Serial.print("\t");
    // Serial.print(digitalRead(8));
    // Serial.print("\t");
    // Serial.println(counter);
/*
ISR(PCINT0_vect)
{
    value++;
}

ISR(PCINT2_vect)
{
    value--;
}*/
