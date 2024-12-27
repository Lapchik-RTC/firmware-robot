#include"regulatori.h"
PIreg::PIreg(float kp, float ki, float maxI, float Ts){
    this->kp = kp;
    this->ki = ki;
    this->maxI = maxI;
    this->Ts = Ts;
}

float PIreg::tick(float err){
    P = err * kp;
    I = I + err * ki * Ts;
    I = constrain(I, -maxI, maxI);
    return P + I;
}

///////////////////   RHex   ///////////////////

sfix RHex::modc(sfix in, sfix modder){
    in += modder;
    while(in > (modder/2.0))
    {
        in -=modder;
    }
    return in;
}

inline sfix RHex::Fc( sfix in, sfix ts, sfix phis )
{
    return in * (phis / ts);
}
inline sfix RHex::Fr0( sfix in, sfix dx, sfix dy )
{
    return in * (dy / dx);
}
inline sfix RHex::Fr( sfix in, sfix ts, sfix dx, sfix dy, sfix phis )
{
    return Fr0(in, dx, dy) + (Fc(ts / 2.0, ts, phis) - Fr0(ts / 2.0, dx, dy));
}
inline sfix RHex::Fl( sfix in, sfix ts, sfix dx, sfix dy, sfix phis )
{
    return -Fr(-in, ts, dx, dy, phis);
}

inline sfix RHex::Ffull(sfix in, sfix ts, sfix tc, sfix phis, sfix phi0)
{
    in = modc(in, tc);
    sfix out;
    if(in < -ts/2.0)
    {
        out = Fl(in, ts, ((tc - ts)/2), (M_PI - (phis/2.0)), phis);
    }
    else if(in < ts/2.0)
    {
        out = Fc(in, ts, phis);
    }
    else
    {
        out = Fr(in, ts, ((tc - ts)/2), (M_PI - (phis/2.0)), phis);
    }
    return out + phi0;
}

///////////////////   Обобщающий класс для лап   ///////////////////
Lapka::Lapka(MotorRegulatorParams *mregp, LegRegParams *lrp):
    MotorRegulatorParams(*mregp),
    LegRegParams(*lrp),
    piReg(mregp->kp, mregp->ki, mregp->maxI, mregp->Ts)
    {

    }
    
float Lapka::getRealSpeed(){
    static int count = 0;
    static int32_t enc = 0;
    static int32_t encCounter = 0;
    static int32_t timer = millis();
    timer = millis();
    while (millis() - timer < 10) {
        noInterrupts();
        count = enc;
        enc = 0;
        interrupts();
        encCounter += count;
    }
  realSpeed = 200.0 * M_PI * (encCounter * 1.0 / /*ENC_PPR*/450);  //скорость в тиках за 10 милисекунд
  encCounter = 0.0;
  timer = millis();
  return realSpeed;
}