#pragma once
#include<Arduino.h>
#include"tcokol.h"

struct MotorConnectParams
{
  byte INA;
  byte INB;
  byte PWM;
};

struct MotorControlParams
{
  float ki;
  float kp;
};

class Motor: public MotorConnectParams, MotorControlParams
{
  public:
  Motor(MotorConnectParams *mconp, MotorControlParams *mctrlp);
  void setGoalSpeed();
  int getGoalSpeed();
  int getRealSpeed();
  
  private:
  int PIreg();
};

class ServoMotor
{
  public:
  Motor motor;

  private:

};

class Lapki
{

};