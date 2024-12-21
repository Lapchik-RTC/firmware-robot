#include<Arduino.h>
#include"tcokol.h"

struct MotorRegulatorParams
{ 
    float Ts;
    float kp;
    float ki;
    float maxI;
};

class PIreg
{
  public:
  PIreg(float kp, float ki, float maxI, float Ts);
  float tick(float err);

  private:
  float kp, ki, maxI;
  float P = 0, I = 0, Ts;
};

class Lapka
{
  public:
  Lapka(MotorRegulatorParams *mregp);
  float getRealSpeed();

  private:
  int realSpeed = 0;;

};