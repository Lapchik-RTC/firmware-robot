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

    void stendUp();

  void l1(float pos){serv1.setGoalPos(pos);};
  void l2(float pos){serv2.setGoalPos(pos);};
  void l3(float pos){serv3.setGoalPos(pos);};
  void l4(float pos){serv4.setGoalPos(pos);};
  void l5(float pos){serv5.setGoalPos(pos);};
  void l6(float pos){serv6.setGoalPos(pos);};

  private:
  float t, tc, ts, phiS, phi0;
  void ork(uint8_t num, float pos);
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

float tc = 6;//6.5;
float ts = 2.5;//4.6;
float phiS = 1.4;
float phi0 = (M_PI/2)+(0.05);

void Orkestr::Foo(float vel){
    updatePhase(t + vel * Ts_s_IN_SEC);
    float kount = int(t / tc) * tc;
    float X = Ffull(t, tc, ts, phiS, phi0);
    float XPi = Ffull(t+M_PI, tc, ts, phiS, phi0);
    float dphi1 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi2 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi3 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi4 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi5 = X;/* + M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi6 = XPi;
    //X = X - tc * floor( (X + (tc*0.5) ) / tc );
    
    l1(/*(2*M_PI*6)+M_PI*/dphi1);
    l4(/*(2*M_PI*6)+M_PI*/dphi4);
    l5(/*(2*M_PI*6)+M_PI*/dphi5);
     
    l2(dphi2/*2*M_PI*6*/);
    l3(dphi3);
    l6(dphi6/*2*M_PI*6*/);
}

void Orkestr::ork(uint8_t num, float pos)
{
    num = constrain(num, 0, 5);
    switch (num)
    {
    case 0:
        l1(pos);
        break;
    case 1:
        l2(pos);
        break;
    case 2:
        l3(pos);
        break;
    case 3:
        l4(pos);
        break;
    case 4:
        l5(pos);
        break;
    case 5:
        l6(pos);
        break;
    default:
        break;
    }
}

void Orkestr::stendUp()
{
    //kalibr

    for(int i = 0; i < 6; i++)
    {
        float kalibrPos = 0;
        while(analogRead(csPins[i]) < trigCurr[i])
        {
            ork(i, kalibrPos);
            kalibrPos -= M_PI/12;
        }
        kalibrPos = 0;
    }
    //
}