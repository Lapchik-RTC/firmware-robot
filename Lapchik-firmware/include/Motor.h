#pragma once
#include <Arduino.h>
#include"Tau.h"
struct MotorConnectParams
{
    int INA;
    int INB;
    int PWM;
    int ENCA;
    int ENCB;
    int ENC_PPR;
    float ke;
    int8_t ENC_DIR;
};

struct MotorControllerParams
{
    float max_speed;
    float maxU;
    float maxUuse;
    float moveU;
    float Ts;
    float kp;
    float ki;
    float speedFilterT;
};


class Motor: public MotorConnectParams, MotorControllerParams
{
    public:
    Motor(MotorConnectParams *mconnp, MotorControllerParams *mctrlp);
    void setSpeed(float speed);
    void encoder();
    void applyU(float u);
    void write(float speed);
    int getEnc();
    //void usePI(bool);
    volatile int enc = 0;

    private:
    bool usePIFlag = 1;
    PIreg piReg;
    Saturation speedLim;
    RateLimiter ULim;
    FOD speedFilter;
    uint64_t timer = 0;
    int8_t motorDir;
    int encCounter = 0;
    float pulses2rad;
    float goalSpeed = 0, realSpeed = 0, angle = 0;
};

//motor ini
Motor::Motor(MotorConnectParams *mconnp, MotorControllerParams *mctrlp)
:MotorConnectParams(*mconnp), MotorControllerParams(*mctrlp), 
speedLim(mctrlp->max_speed*-1, mctrlp->max_speed),
ULim(mctrlp -> Ts, 9999),
speedFilter(mctrlp->Ts, mctrlp->speedFilterT, true),
piReg(mctrlp->Ts, kp, ki, maxU)
{
    this->pulses2rad = 2.0*M_PI / ENC_PPR;
    motorDir = this->pulses2rad > 0 ? 1 : -1;
    pinMode(INA, OUTPUT);
    pinMode(INB, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);
}


void Motor::encoder(){
    bool dir = digitalRead(ENCA)^digitalRead(ENCB);
    enc += dir ? ENC_DIR : -ENC_DIR;
}

// void Motor::usePI(bool enablePI)
// {
//     usePIFlag = enablePI;
// }

void Motor::setSpeed(float speed){
    float goalSpeed = speedLim.tick(speed);
}


void Motor::applyU(float u){
    u *= motorDir;
    if(u == constrain(u, -moveU, moveU))
    {
         u = 0;
    }
    u = constrain(u, -maxUuse, maxUuse);
    int pwm = ULim.tick(u) / maxU * 255;// ограничение и перевод U в шим
    
    if (pwm > 255)
        pwm = 255;
    if (pwm < -255)
        pwm = -255;

    if (pwm >= 0)
    {
        digitalWrite(INB, HIGH);
        digitalWrite(INA, LOW);
        analogWrite(PWM, pwm);
    }
    else
    {
        digitalWrite(INB, LOW);
        digitalWrite(INA, HIGH);
        analogWrite(PWM, -pwm);
    }
}


void Motor::write(float speed){
    setSpeed(speed);
    noInterrupts();
    int c = enc;
    enc = 0;
    interrupts();

    timer = millis();
    encCounter += c;
    angle += c * pulses2rad;
    realSpeed = speedFilter.tick(angle);

    float feedforwardU = goalSpeed * ke;

    //float feedbackU = usePIFlag ? piReg.tick(goalSpeed - realSpeed) : 0;



    float err = goalSpeed - realSpeed;
    static float integral = 0, prevErr = 0;
    integral = constrain(integral + (float)err * ki, -maxUuse, maxUuse);
    
    prevErr = err;
    float feedbackU = constrain(err * kp + integral, -maxUuse, maxUuse);
    //out = kp * in + ki * I.tick(in);

    applyU(feedforwardU + feedbackU);
}

int Motor::getEnc(){
    return enc;
}

// (вход, установка, п, и, д, период в секундах, мин.выход, макс. выход)
int PID(float input, float setpoint, float kp, float ki, float kd, float dt, int minOut, int maxOut) {
  float err = setpoint - input;
  static float integral = 0, prevErr = 0;
  integral = constrain(integral + (float)err * dt * ki, minOut, maxOut);
  float D = (err - prevErr) / dt;
  prevErr = err;
  return constrain(err * kp + integral + D * kd, minOut, maxOut);
}