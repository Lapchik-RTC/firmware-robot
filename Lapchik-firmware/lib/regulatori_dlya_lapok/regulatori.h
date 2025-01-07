#pragma once
#include<Arduino.h>
//#include"tcokol.h"
struct MotorConnectParams
{
    byte INA;
    byte INB;
    byte PWM;
    int dir;
};
struct MotorControlParams
{
  float ki;
  float kp;
  float Ts_s;
  float maxI;
};

////////////////////   KOSTYL   ////////////////////
class DvigatelK: MotorParams
{
    public:
    DvigatelK(MotorParamsK *MP, MotorControlParams *mconp):MotorParamsK(*MP), MotorControlParams(*mconp)
    {
        pinMode(MP->INA, 1);
        pinMode(MP->INB, 1);
    }
    private:
    void motor(float vel);
    float PIreg(float err);
};

void DvigatelK::motor(float vel)
{
    digitalWrite(INA, (vel>0)*dir);
    digitalWrite(INB, (vel>0)*-dir);
}

////////////////////////////////////////////////////
// class SpeedController: public MotorConnectParams, MotorControlParams
// {
//   public:

//   SpeedController(MotorConnectParams *mp, MotorControlParams *mctrlp);
//   void setGoalSpeed();
//   int getGoalSpeed();
//   int getRealSpeed();
  
//   private:
//   int PIreg();
// };

class ServoMotor: MotorConnectParams, MotorControlParams
{
  public:
  ServoMotor(MotorConnectParams *mp, MotorControlParams *mconp);

  private:
  void writePwm(float pwm);
  float PIreg(float err);

};

class Lapki
{

};