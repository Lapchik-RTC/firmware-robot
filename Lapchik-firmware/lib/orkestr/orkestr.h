#pragma once
#include<Arduino.h>
#include "obekti.h"
/////////////////////   Orkestr   ///////////////////////

class Orkestr
{
  public:
  void tripod(/*float forw, float ang*/);
  //void hexopod();
  void setParams(float t, float tc, float ts, float phiS, float phi0);

  private:
  float t_, tc_, ts_, phiS_, phi0_;
//  float modc(float in, float modder);
//   inline float Fc(float, float);
//   inline float Fr0(float, float);
//   inline float Fcomp(float, float, float);
//   inline float Fr(float, float, float, float);
//   inline float Fl(float, float, float, float);
//   inline float Ffull(float, float, float, float, float);
};
void setParams(float t, float tc, float ts, float phiS, float phi0)
{
    
}
void Orkestr::tripod(/*float forw, float ang*/)
{
    float move = 3.0/*Ffull()*/;

    dvigatel_1.update_speed_in_rad(
        serv1.setGoalSpeed( 
            serv1.setPoint( enc_3.get_phi(), enc_1.get_phi() ), enc_1.get_w_moment_rad()
        )
    );

    dvigatel_2.update_speed_in_rad(
        serv2.setGoalSpeed( 
            serv2.setPoint( enc_3.get_phi(), enc_2.get_phi() ), enc_2.get_w_moment_rad()
        )
    );

    dvigatel_4.update_speed_in_rad(
        serv4.setGoalSpeed( 
            serv4.setPoint( enc_3.get_phi(), enc_4.get_phi() ), enc_4.get_w_moment_rad()
        )
    );

    dvigatel_5.update_speed_in_rad(
        serv5.setGoalSpeed( 
            serv5.setPoint( enc_3.get_phi(), enc_5.get_phi() ), enc_5.get_w_moment_rad()
        )
    );  

    dvigatel_6.update_speed_in_rad(
        serv6.setGoalSpeed( 
            serv6.setPoint( enc_3.get_phi(), enc_6.get_phi() ), enc_6.get_w_moment_rad()
        )
    );
    
    Serial.println(enc_5.get_phi());
}

///////////////////////////////////////////////////////////////
/*
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
}*/