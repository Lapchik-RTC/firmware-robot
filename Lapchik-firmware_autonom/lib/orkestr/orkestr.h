#pragma once
#include<Arduino.h>
#include "encoder.h"
#include "regulatori.h"
#include "obekti.h"
#include "f.h"

int sgn(float in)
{
    if(in > 0) return 1;
    else if(in < 0) return -1;
    else return 0;
}


void statPosUpd()
{
    posStatic[0] = enc_1.get_phi();
    posStatic[1] = enc_2.get_phi();
    posStatic[2] = enc_3.get_phi();
    posStatic[3] = enc_4.get_phi();
    posStatic[4] = enc_5.get_phi();
    posStatic[5] = enc_6.get_phi();
}

/////////////////////   Orkestr   ///////////////////////

class Orkestr
{
  public:
  
  void setParams(float t, float tc, float ts, float phiS, float phi0);
  void calibr();
  void stendUp();
 
  /// @brief Foo params
  void setPhiAll(float nPhiL, float nPhiR);

  //___STATES___
  /// @brief Forw
  void Foo(float vel);

  /// @brief Back
  void ReversFoo(float velL, float velR);

  /// @brief Foo Synchro
  void onePhase(float vel);

  /// @brief calibr
  void ostCalibr();  

  /// @brief Turn
  void turnL(float vel);
  void turnR(float vel);
  
  
  void allEncZero();

  float t, t2, tc, ts, phiS, phi0;

  private:

  float X, XPi;
  bool kalibrON1 = 1, kalibrON2 = 1, kalibrON3 = 1, kalibrON4 = 1, kalibrON5 = 1, kalibrON6 = 1;
  uint32_t preKalibrTimer = millis();
  uint32_t calibrTime = millis();
  uint32_t whaitPos = millis();
  
  void updatePhase(float t_, float);

  void l1(float pos){serv1.setGoalPos(pos);};
  void l2(float pos){serv2.setGoalPos(pos);};
  void l3(float pos){serv3.setGoalPos(pos);};
  void l4(float pos){serv4.setGoalPos(pos);};
  void l5(float pos){serv5.setGoalPos(pos);};
  void l6(float pos){serv6.setGoalPos(pos);};  
};

////////////////////////////////////////////////////////////////////////////////////////////////

void Orkestr::setParams(float t_, float tc_, float ts_, float phiS_, float phi0_)
{
    this->t = t_;
    this->t2 = t_;
    this->tc = tc_;
    this->ts = ts_;
    this->phiS = phiS_;
    this->phi0 = phi0_;
}

void Orkestr::updatePhase(float t_, float t2_)
{
    this->t += t_;
    this->t2 += t2_;
}

void Orkestr::Foo(float vel){
    updatePhase(vel * Ts_s_IN_SEC, vel * Ts_s_IN_SEC);

    X = Ffull(t * abs(sgn(vel)), tc, ts, phiS, phi0 + ((M_PI/6.0)* abs(sgn(vel))));
    XPi = Ffull( (t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc, ts, phiS, phi0);
    // XPi = X;
    float dphi1 = X;
    float dphi2 = XPi;
    float dphi3 = XPi;
    float dphi4 = X;
    float dphi5 = X;
    float dphi6 = XPi;
    
    
    l1(dphi1);
    l4(dphi4);
    l5(dphi5);
    l2(dphi2);
    l3(dphi3);
    l6(dphi6);
}

void Orkestr::calibr()
{
    ///// preKalibr /////
    
    float pKvel = -0.2;
    kalibrON1 = 1;
    kalibrON2 = 1;
    kalibrON3 = 1;
    kalibrON4 = 1;
    kalibrON5 = 1;
    kalibrON6 = 1;
    while(millis() - preKalibrTimer < 1500)
    {
        serv1.setGoalSpeed(pKvel);
        serv2.setGoalSpeed(pKvel);
        serv3.setGoalSpeed(pKvel);
        serv4.setGoalSpeed(pKvel);
        serv5.setGoalSpeed(pKvel);
        serv6.setGoalSpeed(pKvel);
    }
    
    /////////////////////
    float vel = -1.6;
    
    int whaitTimeCalibr = 1500;
    ///  dv1  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_1) < TRIG_CUR_1 && kalibrON1 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv1.setGoalSpeed(vel);
    }
    kalibrON1 = 0;
    serv1.setGoalSpeed(0);

    ///  dv2  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_2) < TRIG_CUR_2 && kalibrON2 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv2.setGoalSpeed(-vel);
    }
    kalibrON2 = 0;
    serv2.setGoalSpeed(0);

    ///  dv3  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_3) < TRIG_CUR_3 && kalibrON3 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv3.setGoalSpeed(-vel);
    }
    kalibrON3 = 0;
    serv3.setGoalSpeed(0);

    ///  dv4  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_4) < TRIG_CUR_4 && kalibrON4 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv4.setGoalSpeed(vel);
    }
    kalibrON4 = 0;
    serv4.setGoalSpeed(0);

    ///  dv5  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_5) < TRIG_CUR_5 && kalibrON5 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv5.setGoalSpeed(vel);
    }
    kalibrON5 = 0;
    serv5.setGoalSpeed(0);

    ///  dv6  ///
    calibrTime = millis();
    while( analogRead(CS_PIN_6) < TRIG_CUR_6 && kalibrON6 && (millis() - calibrTime < whaitTimeCalibr))
    {
        serv6.setGoalSpeed(-vel);
    }
    kalibrON6 = 0;
    serv6.setGoalSpeed(0);
    
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
}

void Orkestr::stendUp()
{
    float startPos = (M_PI/2.0) + (M_PI/30.0);
    setPhiAll(startPos, startPos);
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
}

void Orkestr::setPhiAll(float nPhiL, float nPhiR)
{
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();

    int _k = -1;
    whaitPos = millis();
    while((millis() - whaitPos < 1500) && (
        (enc_6.get_phi() < nPhiL * 0.8) || (enc_6.get_phi() < (nPhiL  + (nPhiL * 0.2)))
        ||
        (enc_1.get_phi() < nPhiR * 0.8) || (enc_1.get_phi() < (nPhiR  + (nPhiR * 0.2)))
        ||
        (enc_2.get_phi() < nPhiL * 0.8) || (enc_2.get_phi() < (nPhiL  + (nPhiL * 0.2)))
        ||
        (enc_3.get_phi() < nPhiL * 0.8) || (enc_3.get_phi() < (nPhiL  + (nPhiL * 0.2)))
        ||
        (enc_4.get_phi() < nPhiR * 0.8) || (enc_4.get_phi() < (nPhiR  + (nPhiR * 0.2)))
        ||
        (enc_5.get_phi() < nPhiR * 0.8) || (enc_5.get_phi() < (nPhiR  + (nPhiR * 0.2)))
    )
    )
    {
        serv1.setGoalPos(nPhiR * _k);
        serv2.setGoalPos(nPhiL);
        serv3.setGoalPos(nPhiL);
        serv4.setGoalPos(nPhiR * _k);
        serv5.setGoalPos(nPhiR * _k);
        serv6.setGoalPos(nPhiL);
    }
}

void Orkestr::ReversFoo(float velL, float velR){
    updatePhase(-(velR * Ts_s_IN_SEC), -(velL * Ts_s_IN_SEC));
  
    X = Ffull(t, tc, ts, phiS, phi0/*-(M_PI/6.0)*/);
    XPi = Ffull(t2+M_PI, tc, ts, phiS, phi0-(M_PI/6.0));

    float dphi1 = X;
    float dphi2 = XPi;
    float dphi3 = XPi;
    float dphi4 = X;
    float dphi5 = X;
    float dphi6 = XPi;
  
    l1(dphi1 + M_PI);
    l4(dphi4 + M_PI);
    l5(dphi5 + M_PI);
    l2(dphi2 + M_PI);
    l3(dphi3 + M_PI);
    l6(dphi6 + M_PI);
}

void Orkestr::onePhase(float vel)
{
    updatePhase(vel * Ts_s_IN_SEC, vel * Ts_s_IN_SEC);
    X = Ffull(t, tc, ts, phiS, phi0+(M_PI/6));
    XPi = Ffull(t, tc, ts, phiS, phi0);
    l1(X);
    l4(X);
    l5(X);
    l2(XPi);
    l3(XPi);
    l6(XPi);
}

void Orkestr::allEncZero()
{
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
}
void Orkestr::ostCalibr()
{    
    uint32_t timeOstCalibr = millis();
    float velOC = -1.0;
    int dir[6] = {1,1,1,1,1,1};
    while (millis() - timeOstCalibr < 3100)
    {       
        if(modc(enc_1.get_phi(), 2.0*M_PI) < M_PI) dir[0] = -1;
        else dir[0] = 1;

        if(modc(enc_2.get_phi(), 2.0*M_PI) < M_PI) dir[1] = -1;
        else dir[1] = 1;

        if(modc(enc_3.get_phi(), 2.0*M_PI) < M_PI) dir[2] = -1;
        else dir[2] = 1;

        if(modc(enc_4.get_phi(), 2.0*M_PI) < M_PI) dir[3] = -1;
        else dir[3] = 1;

        if(modc(enc_5.get_phi(), 2.0*M_PI) < M_PI) dir[4] = -1;
        else dir[4] = 1;

        if(modc(enc_6.get_phi(), 2.0*M_PI) < M_PI) dir[5] = -1;
        else dir[5] = 1;

        serv1.setGoalSpeed(velOC * dir[0]);
        serv2.setGoalSpeed(velOC * dir[1]);
        serv3.setGoalSpeed(velOC * dir[2]);
        serv4.setGoalSpeed(velOC * dir[3]);
        serv5.setGoalSpeed(velOC * dir[4]);
        serv6.setGoalSpeed(velOC * dir[5]);
    }
    velOC = -0.3;
        serv1.setGoalSpeed(velOC * dir[0]);
        serv2.setGoalSpeed(velOC * dir[1]);
        serv3.setGoalSpeed(velOC * dir[2]);
        serv4.setGoalSpeed(velOC * dir[3]);
        serv5.setGoalSpeed(velOC * dir[4]);
        serv6.setGoalSpeed(velOC * dir[5]);
    calibr();
    stendUp();
}

void Orkestr::turnR(float vel)
{
    updatePhase(-(vel * Ts_s_IN_SEC), (vel * Ts_s_IN_SEC));
    
    X = Ffull(t, tc, ts, phiS, phi0);
    XPi = Ffull(t2 + M_PI, tc, ts, phiS, phi0);
    
    float L1 = X;
    float L2 = Ffull(t + M_PI, tc, ts, phiS, phi0+(M_PI/6.0));
    float R1 = XPi;
    float R2 = Ffull(t2, tc, ts, phiS, phi0+(M_PI/6.0));
  
    l1(L1);
    l4(R2);
    l5(L1);

    l2(R1);
    l3(L2);
    l6(R1);
}

void Orkestr::turnL(float vel)
{    
    updatePhase((vel * Ts_s_IN_SEC), -(vel * Ts_s_IN_SEC));
    
    X = Ffull(t, tc, ts, phiS, phi0);
    XPi = Ffull(t2 + M_PI, tc, ts, phiS, phi0);
    
    float L1 = X;
    float L2 = Ffull(t + M_PI, tc, ts, phiS, phi0+(M_PI/6.0));
    float R1 = XPi;
    float R2 = Ffull(t2, tc, ts, phiS, phi0+(M_PI/6.0));
  
    l1(L1);
    l4(R2);
    l5(L1);

    l2(R1);
    l3(L2);
    l6(R1);
}
Orkestr robot;