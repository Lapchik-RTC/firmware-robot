#pragma once
#include<Arduino.h>
#include "obekti.h"
#include "f.h"
/////////////////////   Orkestr   ///////////////////////

class Orkestr
{
  public:
  //void hexopod();
  void setParams(float t, float tc, float ts, float phiS, float phi0);
  void updatePhase(float t_);
  void Foo(float vel);

  void l1(float pos){serv1.setGoalPos(pos);};
  void l2(float pos){serv2.setGoalPos(pos);};
  void l3(float pos){serv3.setGoalPos(pos);};
  void l4(float pos){serv4.setGoalPos(pos);};
  void l5(float pos){serv5.setGoalPos(pos);};
  void l6(float pos){serv6.setGoalPos(pos);};

  private:
  float t, tc, ts, phiS, phi0;
  //////////
};


void Orkestr::setParams(float t_, float tc_, float ts_, float phiS_, float phi0_)
{
    this->t = t_;
    this->tc = tc_;
    this->ts = ts_;
    this->phiS = phiS_;
    this->phi0 = phi0_;
}

void Orkestr::updatePhase(float t_)
{
    this->t = t_;
}

float tc = 8.0;
float ts = 4.6;
float phis = 1.5;
float phi0 = 0.0;
void Orkestr::Foo(float vel){
    updatePhase(t + vel * Ts_s_IN_SEC);
    float kount = int(t / tc) * tc;
    float dphi1 = 10;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi2 = 10;//kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi3 = 10;//kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi4 = 10;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi5 = 10;//kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    
    float X = Ffull(t, tc, ts, phis, phi0);
    //X = X - tc * floor( (X + (tc*0.5) ) / tc );
    
    
    float dphi6 = X;//Ffull(X, tc, ts, phis, phi0);
    
    //float dphi6 = kount + F_shtrih(t, tc, ts, phiS, phi0);
    // if(t > tc)
    // {
    //     t = 0;
    //     enc_1.encZero();
    //     enc_2.encZero();
    //     enc_3.encZero();
    //     enc_4.encZero();
    //     enc_5.encZero();
    //     enc_6.encZero();
    // }

    Serial.print(t);
    Serial.print("\tdphi6: ");
    Serial.print(dphi6);
    Serial.print('\n');
    
    // l1(dphi1);
    // l2(dphi2);
    // l3(dphi3);
    // l4(dphi4);
    l6(dphi6);
    //l6(dphi6);
}

///////////////////////////////////////////////////////////////

// inline float Orkestr::Fc(float t, float phiS_ts)
// {
//     return t*phiS_ts;
// }

// inline float Orkestr::Fr0(float t, float dxdy)
// {
//     return t*dxdy;
// }

// inline float Orkestr::Fcomp(float ts, float phiS_ts, float dxdy)
// {
//     return Fc(ts*0.5, phiS_ts) - Fr0(ts*0.5, dxdy);
// }

// inline float Orkestr::Fr(float t, float ts, float phiS_ts, float dxdy)
// {
//     return Fr0(t, dxdy) + Fcomp(ts, phiS_ts, dxdy);
// }

// inline float Orkestr::Fl(float t, float ts, float phiS_ts, float dxdy)
// {
//     return -Fr(t, ts, phiS_ts, dxdy);
// }

// inline float Orkestr::Ffull(float t, float tc, float ts, float phiS, float phi0)
// {
//     t = modc(t, tc);
//     float out_;
//     float phiS_ts = phiS/ts;
//     if( t < -(ts*0.5))
//     {
//         float dxdy = (( 2*M_PI ) - phiS) / (tc - ts);
//         out_ = Fl(t, ts, phiS_ts, dxdy);
//         Serial.print(".");
//     }
//     else if( t < (ts*0.5))
//     {
//         out_ = Fc(t, phiS_ts);
//         Serial.print(":");
//     }
//     else
//     {
//         float dydx = (( 2*M_PI ) - phiS) / (tc - ts);
//         out_ = Fr(t, ts, phiS_ts, dydx);
//         Serial.print(";");
//     }
//     return out_+phi0;
// }


