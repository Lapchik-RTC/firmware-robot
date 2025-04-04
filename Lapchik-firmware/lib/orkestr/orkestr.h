#pragma once
#include<Arduino.h>
#include "obekti.h"
#include "f.h"

int sgn(float in)
{
    if(in >= 0) return 1;
    else return -1;
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
  /// @brief --- 
  void moonwalk(float);

  

  void asynchroFoo(float velL, float velR);
  
  void ostanovka();

  void turnL(float vel);
  void turnR(float vel);

  private:
  float t, t2, tc, ts, phiS, phi0;
  float X, XPi;
  bool kalibrON1 = 1, kalibrON2 = 1, kalibrON3 = 1, kalibrON4 = 1, kalibrON5 = 1, kalibrON6 = 1;
  bool zeroAll = 1;
  uint32_t preKalibrTimer = millis();
  uint32_t whaitPos = millis();
  uint32_t whaitPosL = millis();
  uint32_t whaitPosR = millis();
  
  void updatePhase(float t_, float);


  void l1(float pos){serv1.setGoalPos(pos);};
  void l2(float pos){serv2.setGoalPos(pos);};
  void l3(float pos){serv3.setGoalPos(pos);};
  void l4(float pos){serv4.setGoalPos(pos);};
  void l5(float pos){serv5.setGoalPos(pos);};
  void l6(float pos){serv6.setGoalPos(pos);};
  void setPhiL(float nPhi){ l2(nPhi); l3(nPhi); l6(nPhi); };
  void setPhiR(float nPhi){ l1(nPhi); l4(nPhi); l5(nPhi); };
  void setPhiSideL(float nPhi){ l2(nPhi); l4(nPhi); l6(nPhi); };
  void setPhiSideR(float nPhi){ l1(nPhi); l3(nPhi); l5(nPhi); };
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

    X = Ffull(t, tc, ts, phiS, phi0+(M_PI/6));
    XPi = Ffull(t + M_PI, tc, ts, phiS, phi0);
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

    Serial.print("X: " + String(enc_4.get_phi()) +" (1, 4, 5)");
    Serial.println("\tXPi: " + String(XPi) +" (2, 3, 6)");
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
    int trig1 = 150;

        int trig2 = 150;//140;
        int trig2_ = 130;
    
        int trig3 = 150;//130;
        int trig3_ = 130;
    
    int trig4 = 150;//135;
    
    int trig5 = 150;//130;
    
        int trig6 = 150;//146;
        int trig6_ = 130;

    ///  dv1  ///
    while( analogRead(csPins[0]) < trig1 && kalibrON1)
    {
        serv1.setGoalSpeed(vel);
    }
    kalibrON1 = 0;
    serv1.setGoalSpeed(0);

    ///  dv2  ///
    while( analogRead(csPins[1]) < trig2 && kalibrON2)
    {
        serv2.setGoalSpeed(-vel);
    }
    kalibrON2 = 0;
    serv2.setGoalSpeed(0);

    ///  dv3  ///
    while( analogRead(csPins[2]) < trig3 && kalibrON3)
    {
        serv3.setGoalSpeed(-vel);
    }
    kalibrON3 = 0;
    serv3.setGoalSpeed(0);

    ///  dv4  ///
    while( analogRead(csPins[3]) < trig4 && kalibrON4)
    {
        serv4.setGoalSpeed(vel);
    }
    kalibrON4 = 0;
    serv4.setGoalSpeed(0);

    ///  dv5  ///
    while( analogRead(csPins[4]) < trig5 && kalibrON5)
    {
        serv5.setGoalSpeed(vel);
    }
    kalibrON5 = 0;
    serv5.setGoalSpeed(0);

    ///  dv6  ///
    while( analogRead(csPins[5]) < trig6 && kalibrON6)
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
    perehodFix = 1;
    serv1.setGoalSpeed(0);
    serv2.setGoalSpeed(0);
    serv3.setGoalSpeed(0);
    serv4.setGoalSpeed(0);
    serv5.setGoalSpeed(0);
    serv6.setGoalSpeed(0);

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

void Orkestr::moonwalk(float vel){
    updatePhase(vel * Ts_s_IN_SEC, -(vel * Ts_s_IN_SEC));

    Serial.print("X: " + String(t) +" (1, 4, 5)");
    Serial.println("\tXPi: " + String(t2) +" (2, 3, 6)");
  
    X = Ffull(t, tc, ts, phiS, phi0/*-(M_PI/6.0)*/);
    XPi = Ffull(t2+M_PI, tc, ts, phiS, phi0-(M_PI/6.0));
    // XPi = X;

    float dphi1 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi2 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi3 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi4 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi5 = X;/* + M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi6 = XPi;
  
    l1(dphi1 + M_PI);
    l4(dphi4 + M_PI);
    l5(dphi5 + M_PI);
    l2(dphi2 + M_PI);
    l3(dphi3 + M_PI);
    l6(dphi6 + M_PI);
}//*/

void Orkestr::ReversFoo(float velL, float velR){
    updatePhase(sgn(velL)*(velR * Ts_s_IN_SEC), sgn(velL)*(velL * Ts_s_IN_SEC));

    // Serial.print("X: " + String(t) +" (1, 4, 5)");
    // Serial.println("\tXPi: " + String(t2) +" (2, 3, 6)");
  
    X = Ffull(t, tc, ts, phiS, phi0/*-(M_PI/6.0)*/);
    XPi = Ffull(t2+M_PI, tc, ts, phiS, phi0-(M_PI/6.0));
    // XPi = X;

    float dphi1 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi2 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi3 = XPi;/*+ M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi4 = X;//kount + Ffull(t, tc, ts, phiS, phi0);
    float dphi5 = X;/* + M_PI;*///kount + Ffull(t, tc, ts, phiS, phi0 + M_PI_2);
    float dphi6 = XPi;
  
    l1(dphi1 + M_PI);
    l4(dphi4 + M_PI);
    l5(dphi5 + M_PI);
    l2(dphi2 + M_PI);
    l3(dphi3 + M_PI);
    l6(dphi6 + M_PI);
}

////////////////////////////////////////////////////////////////////////
void Orkestr::ostanovka()
{
    uint32_t timeOst = millis();
    while (millis() - timeOst < 1500)
    {    
        serv2.setGoalPos(posStatic[1]);
        serv3.setGoalPos(posStatic[2]);
        serv6.setGoalPos(posStatic[5]);  
        serv1.setGoalPos(posStatic[0]);
        serv4.setGoalPos(posStatic[3]);
        serv5.setGoalPos(posStatic[4]);
    }
    float dPos[6] = {0,0,0,0,0,0};
    float rPos[6] = {enc_1.get_phi(), enc_2.get_phi(), enc_3.get_phi(), enc_4.get_phi(), enc_5.get_phi(), enc_6.get_phi()};
    for(int i = 0; i < 6; i++)
    {
        if(modc(rPos[i], 2.0*M_PI) < M_PI)
        {
            dPos[i] = M_PI - rPos[i];
        }
        else
        {
            dPos[i] = 2.0*M_PI - rPos[i];
        }
    }
    serv2.setGoalPos(dPos[1]);
    serv3.setGoalPos(dPos[2]);
    serv6.setGoalPos(dPos[5]);  
    serv1.setGoalPos(dPos[0]);
    serv4.setGoalPos(dPos[3]);
    serv5.setGoalPos(dPos[4]);

    // statPosUpd();
    // float gPosL = 0, gPosR = 0;
    //
    // if(X <= M_PI)
    // {
    //     gPosR = M_PI - X;
    // }
    // else
    // {
    //     gPosR = 2.0*M_PI - X;
    // }
    //
    // if(XPi <= M_PI)
    // {
    //     gPosL = M_PI - XPi;
    // }
    // else
    // {
    //     gPosL = 2.0*M_PI - XPi;
    // }
    // perehodFix = 0;
    // float ust = M_PI;
    // // setPhiAll(gPosL + ust, gPosR + ust);
    // whaitPos = millis();
    // float tochnost = 1.0;
    // while((millis() - whaitPos < 10000) && (
    //     (enc_1.get_phi() < (gPosR + ust) * tochnost || (enc_1.get_phi() < ((gPosR + ust)  + ((gPosR + ust) * (1.0 - tochnost)))))||
    //     (enc_2.get_phi() < (gPosL + ust) * tochnost || (enc_2.get_phi() < ((gPosL + ust)  + ((gPosL + ust) * (1.0 - tochnost)))))||
    //     (enc_3.get_phi() < (gPosL + ust) * tochnost || (enc_3.get_phi() < ((gPosL + ust)  + ((gPosL + ust) * (1.0 - tochnost)))))||
    //     (enc_4.get_phi() < (gPosR + ust) * tochnost || (enc_4.get_phi() < ((gPosR + ust)  + ((gPosR + ust) * (1.0 - tochnost)))))||
    //     (enc_5.get_phi() < (gPosR + ust) * tochnost || (enc_5.get_phi() < ((gPosR + ust)  + ((gPosR + ust) * (1.0 - tochnost)))))||
    //     (enc_6.get_phi() < (gPosL + ust) * tochnost || (enc_6.get_phi() < ((gPosL + ust)  + ((gPosL + ust) * (1.0 - tochnost)))))
    // )
    // )
    // {
    //     serv2.setGoalPos(/*posStatic[1] + */gPosL + ust);
    //     serv3.setGoalPos(/*posStatic[2] + */gPosL + ust);
    //     serv6.setGoalPos(/*posStatic[5] + */gPosL + ust);  
    //     serv1.setGoalPos(/*posStatic[0] + */gPosR + ust*0.5);
    //     serv4.setGoalPos(/*posStatic[3] + */gPosR + ust*0.5);
    //     serv5.setGoalPos(/*posStatic[4] + */gPosR + ust*0.5);
    // }
    // // statPosUpd();
    // // serv2.setGoalPos(posStatic[1]+(M_PI/6.0));
    // // serv3.setGoalPos(posStatic[2]+(M_PI/6.0));
    // // serv6.setGoalPos(posStatic[5]+(M_PI/6.0));  
    // // serv1.setGoalPos(posStatic[0]+(M_PI/6.0)+ust*0.5);
    // // serv4.setGoalPos(posStatic[3]+(M_PI/6.0)+ust*0.5);
    // // serv5.setGoalPos(posStatic[4]+(M_PI/6.0)+ust*0.5);
    // // serv1.setGoalSpeed(0);
    // // serv2.setGoalSpeed(0);
    // // serv3.setGoalSpeed(0);
    // // serv4.setGoalSpeed(0);
    // // serv5.setGoalSpeed(0);
    // // serv6.setGoalSpeed(0);
    // perehodFix = 1;

}

void Orkestr::turnL(float vel)
{
    updatePhase(vel * Ts_s_IN_SEC, vel * Ts_s_IN_SEC);

    float fPos = Ffull(t, tc, ts, phiS, phi0+(M_PI/6));
    float fPosPi = Ffull(t + M_PI, tc, ts, phiS, phi0);
    ///////////////////////////////////////////
    serv2.setGoalPos(posStatic[1]);
    serv4.setGoalPos(posStatic[3]);
    serv6.setGoalPos(posStatic[5]);

    serv1.setGoalPos(fPos);
    serv3.setGoalPos(fPosPi);
    serv5.setGoalPos(fPos);
}