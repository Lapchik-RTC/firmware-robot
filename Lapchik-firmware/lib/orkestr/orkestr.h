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
    float X = Ffull(t, tc, ts, phis, phi0);
    float XPi = Ffull(t+M_PI, tc, ts, phis, phi0);
    float dphi1 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi2 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi3 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi4 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi5 = XPi;/* + M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi6 = X;
    //X = X - tc * floor( (X + (tc*0.5) ) / tc );
    
    l1(dphi1);
    l2(dphi2);
    l3(dphi3);
    l4(dphi4);
    l5(dphi5);
    l6(dphi6);
}

