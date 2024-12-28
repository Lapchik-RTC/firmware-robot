#include<Arduino.h>
#include"tcokol.h"

typedef float sfix;

///////////////////   PI   ///////////////////
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

///////////////////   Регулятор лапки   ///////////////////
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

struct LegRegParams
{
  const sfix tc;
  const sfix ts;
  const sfix phis;
  const sfix phi0;
};

///////////////////___в_main___///////////////////
LegRegParams lrp = {
  .tc = (sfix(2*M_PI)),
  .ts = (sfix(2*2/3.6*M_PI)),
  .phis = (sfix(1.5)),
  .phi0 = (sfix(-2))
};
///////////////////___в_main___///////////////////


class Lapka: public MotorRegulatorParams, public LegRegParams
{
  public:
  Lapka(MotorRegulatorParams *mregp, LegRegParams *lrp);
  float getRealSpeed();
  void apply();

  private:
  PIreg piReg;
  RHex legReg;
  int realSpeed = 0;
  sfix leg_phase;
  sfix forward_velocity, angular_velocity;
  void legPhaseUpd();
};