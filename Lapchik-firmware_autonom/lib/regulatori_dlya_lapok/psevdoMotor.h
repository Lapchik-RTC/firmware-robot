#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
struct MotorParams
{
    byte inA;
    byte inB;
    byte pwmPin;
    byte csPin;
    int ppr;
    int motorDir;
};

class Dvigatel:MotorParams
{
    public:
    Dvigatel(MotorParams *mconp)
    :MotorParams(*mconp)
    {
        pinMode(this->inA, 1);
        pinMode(this->inB, 1);
    }
    void write(int vel){
        digitalWrite(inA, vel * motorDir);
        digitalWrite(inA, vel * -motorDir);
        analogWrite(pwmPin, min(abs(vel), 255));
    }
};
#endif