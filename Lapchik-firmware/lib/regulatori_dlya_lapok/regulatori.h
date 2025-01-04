#pragma once
#include<Arduino.h>
#include"tcokol.h"

struct MotorControlParams
{
  float ki;
  float kp;
};

class SpeedController: public MotorParams, MotorControlParams
{
  public:

  SpeedController(MotorParams *mp, MotorControlParams *mctrlp);
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