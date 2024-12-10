#include <Arduino.h>
#include"Motor.h"
#include "Defines.h"
MotorConnectParams mconp = {
    .INA = 39,
    .INB = 37,
    .PWM = 7,
    .ENCA = 2,
    .ENCB = 27,
    .ENC_PPR = 465,
    .ke = MOTORS_KE,
    .ENC_DIR = 1
};
MotorControllerParams mctrlp = {
    .max_speed = MAX_SPEED,
    .maxU = 25,
    .maxUuse = 10,
    .moveU = 1,
    .Ts = Ts_s,
    .kp = MOTORS_PI_GAIN,
    .ki = MOTORS_PI_KI,
    .speedFilterT = 2*Ts_s
};
Motor motor(&mconp, &mctrlp);

void setup(){
    attachInterrupt(digitalPinToInterrupt(mconp.ENCA), [](){motor.encoder();}, FALLING);
    Serial.begin(9600);
}
void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_us){
        motor.write(1.0);
    }
    timer = micros();
    //Serial.println(motor.enc);
    /*digitalWrite(39, 1);
    digitalWrite(37, 0);
    analogWrite(7, 10);*/
}