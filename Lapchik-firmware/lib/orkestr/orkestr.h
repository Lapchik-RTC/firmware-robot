#pragma once
#include<Arduino.h>
#include "obekti.h"
/////////////////////   Orkestr   ///////////////////////

class Orkestr
{
  public:
  void tripod(float forw, float ang);
  //void hexopod();
  void setParams(float t, float tc, float ts, float phiS, float phi0);

  private:
  float t_, tc_, ts_, phiS_, phi0_;
  float modc(float in, float modder);
  inline Fc(float, float);
  inline Fr0(float, float);
  inline Fcomp(float, float, float);
  inline Fr(float, float, float, float);
  inline Fl(float, float, float, float);
  inline Ffull(float, float, float, float, float);
};
void setParams(float t, float tc, float ts, float phiS, float phi0)
{
    
}
void Orkestr::tripod(float forw, float ang)
{
    float move = Ffull()

    serv1.setAngle();
    serv4.setAngle();
    serv5.setAngle();

    serv2.setAngle();
    serv3.setAngle();
    serv6.setAngle();
}

///////////////////////////////////////////////////////////////
inline float Orkestr::Fc(float t, float phiS_ts)
{
    return t*phiS_ts;
}

inline float Orkestr::Fr0(float t, float dxdy)
{
    return t*dxdy;
}

inline float Orkestr::Fcomp(float ts, float phiS_ts, float dxdy)
{
    return Fc(ts*0.5, phiS_ts) - Fr0(ts*0.5, dxdy);
}

inline float Orkestr::Fr(float t, float ts, float phiS_ts, float dxdy)
{
    return Fr0(t, dxdy) + Fcomp(ts, phiS_ts, dxdy);
}

inline float Orkestr::Fl(float t, float ts, float phiS_ts, float dxdy)
{
    return -Fr(t, ts, phiS_ts, dxdy);
}

inline float Orkestr::Ffull(float t, float tc, float ts, float phiS, float phi0)
{
    t = modc(t, tc);
    float out;
    float phiS_ts = phiS/ts;
    if( t < -(ts*0.5))
    {
        float dxdy = (( 2*M_PI ) - phiS_ts) / (tc - ts);
        out = Fl(t, ts, phists, dydx);
    }
    else if( t < (ts*0.5))
    {
        out = Fc(t, phiS_ts);
    }
    else
    {
        float dydx = (( 2*M_PI ) - phiS) / (tc - ts);
        out = Fr(t, ts, phiS_ts, dydx);
    }
}

float Orkestr::modc(float in, float modder)
{
    in = in + modder;
    while(in > modder*sfix(0.5))
    {
        in = in - modder;
    }
    return in;
}