#include<Arduino.h>
#include"tcokol.h"

typedef float sfix;

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

class RHex
{
  typedef float sfix;
  public:
  inline sfix Ffull(sfix t, sfix ts, sfix tc, sfix phis, sfix phi0);

  private:
  sfix modc(sfix in, sfix modder);
  inline sfix Fc(sfix in, sfix ts, sfix phis);
  inline sfix Fr0(sfix in, sfix dx, sfix dy);
  inline sfix Fr(sfix in, sfix ts, sfix dx, sfix dy, sfix phis);
  inline sfix Fl(sfix in, sfix ts, sfix dx, sfix dy, sfix phis);
  };