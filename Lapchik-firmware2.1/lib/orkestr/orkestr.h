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
    // posStatic[0] = enc_1.get_phi();
    // posStatic[1] = enc_2.get_phi();
    // posStatic[2] = enc_3.get_phi();
    // posStatic[3] = enc_4.get_phi();
    // posStatic[4] = enc_5.get_phi();
    // posStatic[5] = enc_6.get_phi();
    for(int i = 0; i < 6; i++)
    {
        posStatic[i] = Enc[i].get_phi();
    }
}

/////////////////////   Orkestr   ///////////////////////

class Orkestr
{
  public:
  
  void setParams(float t, float tc, float ts, float phiS, float phi0, float delta_ts = 0.0, float delta_phi0 = 0.0);

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
  void calibr();  
  void stendUp();
  void allEncZero();

  /// @brief Turn
  void turnL(float vel);
  void turnR(float vel);
  void ShiftTurnR(float vel);
  void ShiftTurnL(float vel);


  float* getPos();
  float getRT(){return t;}
  
  void ladFoo(float vel);
  float X1, X2, X3;
  float t, t2, tc, ts, phiS, phi0, delta_ts, delta_phi0;

  private:

  float X, XPi;
  bool kalibrON1 = 1, kalibrON2 = 1, kalibrON3 = 1, kalibrON4 = 1, kalibrON5 = 1, kalibrON6 = 1;
  uint32_t preKalibrTimer = millis();
  uint32_t calibrTime = millis();
  uint32_t whaitPos = millis();
  
    bool firstCalibr = 1;
    bool endCalibr[6] = {0,0,0,0,0,0};
    uint32_t ladXChange = 0;
    bool endLad = 1;
  void updatePhase(float t_, float t2_);
public:
  void l1(float pos){privod[0].setPos(pos);};
  void l2(float pos){privod[1].setPos(pos);};
  void l3(float pos){privod[2].setPos(pos);};
  void l4(float pos){privod[3].setPos(pos);};
  void l5(float pos){privod[4].setPos(pos);};
  void l6(float pos){privod[5].setPos(pos);};  
};

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////   Foo   //////////////
void Orkestr::setParams(float t_, float tc_, float ts_, float phiS_, float phi0_, float delta_ts_ = 0.0, float delta_phi0_ = 0.0)
{
    this->t = t_;
    this->t2 = t_;
    this->tc = tc_;
    this->ts = ts_;
    this->phiS = phiS_;
    this->phi0 = phi0_;
    this->delta_ts = delta_ts_;
    this->delta_phi0 = delta_phi0_;
}

void Orkestr::updatePhase(float t_, float t2_)
{
    this->t += t_;
    this->t2 += t2_;
}

void Orkestr::Foo(float vel){
    updatePhase(vel * Ts_s_IN_SEC, vel * Ts_s_IN_SEC);
    
    X   = Ffull(t, tc, ts, phiS, phi0);
    XPi = Ffull(t + M_PI, tc, ts, phiS, phi0);

    privod[0].setPos(X);
    privod[2].setPos(XPi);
    privod[4].setPos(X);
    
    privod[1].setPos(XPi);
    privod[3].setPos(X);   
    privod[5].setPos(XPi);
    
    // privod[0].setPos(Ffull(t + ( (Enc[0].getCorr()/kolvTickRate[0])*2.0*M_PI ), tc, ts, phiS, phi0)); 
    // privod[2].setPos(Ffull(t + ( (Enc[2].getCorr()/kolvTickRate[2])*2.0*M_PI )+M_PI, tc, ts, phiS, phi0));
    // privod[4].setPos(Ffull(t + ( (Enc[4].getCorr()/kolvTickRate[4])*2.0*M_PI ), tc, ts, phiS, phi0));
    
    // privod[1].setPos(Ffull(t + ( (Enc[1].getCorr()/kolvTickRate[1])*2.0*M_PI )+M_PI, tc, ts, phiS, phi0));
    // privod[3].setPos(Ffull(t + ( (Enc[3].getCorr()/kolvTickRate[3])*2.0*M_PI ), tc, ts, phiS, phi0));   
    // privod[5].setPos(Ffull(t + ( (Enc[5].getCorr()/kolvTickRate[5])*2.0*M_PI )+M_PI, tc, ts, phiS, phi0));
}

//////////////   Enc   //////////////
void Orkestr::allEncZero()
{
    for(int i = 0; i < 6; i++)
    {
        Enc[i].encZero();
    }
}

//////////////   Calibr   //////////////
void Orkestr::calibr()
{   
    int pVel = 1.2;
    preKalibrTimer = millis();
    while(millis() - preKalibrTimer < 1700)
    {
        for(int i = 0; i < 6; i++)
        {
            privod[i].setSpeed(pVel);
        }
    }
    for(int i = 0; i < 6; i++)
    {
        privod[i].setSpeed(pVel);
    }

    float vel = 3.0;
    int whaitTimeCalibr_ = 4000;
    for(int i = 0; i < 6; i++) endCalibr[i] = false;
    calibrTime = millis();

    while( ((analogRead(CS_PIN_1) < TRIG_CUR_1) ||
           (analogRead(CS_PIN_4) < TRIG_CUR_4) || 
           (analogRead(CS_PIN_5) < TRIG_CUR_5) || 

           (analogRead(CS_PIN_2) < TRIG_CUR_2) ||
           (analogRead(CS_PIN_3) < TRIG_CUR_3) ||
           (analogRead(CS_PIN_6) < TRIG_CUR_6)) &&
           (millis() - calibrTime < whaitTimeCalibr_)
        )
    {   
        for(int i = 0; i < 6; i++){
            ///  dv1  ///
            if(analogRead(csPin[i]) < trigCur[i] && (endCalibr[i] == false))
            {
                privod[i].setSpeed(vel);
            }
            else
            {
                if(endCalibr[i] == false)
                    Enc[i].encZero();
                endCalibr[i] = true;
                privod[i].setPos(0);
            }
        }
    }
    for(int i = 0; i < 6; i++) endCalibr[i] = false;

    allEncZero();
    stendUp();
    allEncZero();
}

void Orkestr::stendUp()
{
    float upSpd = 4.0;
    for(int i = 0; i < 6; i++) endCalibr[i] = false;
    calibrTime = millis();
    while
    (
        ((modc(Enc[0].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(Enc[1].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(Enc[2].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(Enc[3].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(Enc[4].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(Enc[5].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) )&&
        ( millis() - calibrTime <  1000)
    )
    {
        for(int i = 0; i < 6; i++)
        {
            if( (modc(Enc[i].get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[i] == false) )
                privod[i].setSpeed(upSpd);
            else
            {
                if(endCalibr[i] == false)
                    Enc[i].encZero();
                endCalibr[i] = 1;
                privod[i].setPos(0);
            }
        }
    }
    for(int i = 0; i < 6; i++) endCalibr[i] = false;
    for(int i = 0; i < 6; i++)
    {
        privod[i].setPos(0);
    } 
}

void Orkestr::setPhiAll(float nPhiL, float nPhiR)
{
    allEncZero();

    int _k = -1;
    whaitPos = millis();
    while((millis() - whaitPos < 1500) && (
        (Enc[5].get_phi() < nPhiL * 0.8) || (Enc[5].get_phi() < (nPhiL  + (nPhiL * 0.2))) ||
        (Enc[0].get_phi() < nPhiR * 0.8) || (Enc[0].get_phi() < (nPhiR  + (nPhiR * 0.2))) ||
        (Enc[1].get_phi() < nPhiL * 0.8) || (Enc[1].get_phi() < (nPhiL  + (nPhiL * 0.2))) ||
        (Enc[2].get_phi() < nPhiL * 0.8) || (Enc[2].get_phi() < (nPhiL  + (nPhiL * 0.2))) ||
        (Enc[3].get_phi() < nPhiR * 0.8) || (Enc[3].get_phi() < (nPhiR  + (nPhiR * 0.2))) ||
        (Enc[4].get_phi() < nPhiR * 0.8) || (Enc[4].get_phi() < (nPhiR  + (nPhiR * 0.2)))
    )
    )
    {
        privod[0].setPos(nPhiR * _k);
        privod[1].setPos(-nPhiL);
        privod[2].setPos(-nPhiL);
        privod[3].setPos(nPhiR * _k);
        privod[4].setPos(nPhiR * _k);
        privod[5].setPos(-nPhiL);
    }
}

/////////////////////////////////////////////

//////////////   Other move   //////////////

/////////////////////////////////////////////

void Orkestr::ReversFoo(float velL, float velR){
    updatePhase(-(velR * Ts_s_IN_SEC), -(velL * Ts_s_IN_SEC));
  
    X = Ffull(t, tc, ts, phiS, phi0-(M_PI/6.0));
    XPi = Ffull(t2+M_PI, tc, ts, phiS, phi0-(M_PI/6.0));

    float dphi1 = X;
    float dphi2 = XPi;
    float dphi3 = XPi;
    float dphi4 = X;
    float dphi5 = X;
    float dphi6 = XPi;
  
    l5(dphi5);
    l3(dphi3);
    l1(dphi1);
    l4(dphi4);
    l2(dphi2);
    l6(dphi6);
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

void Orkestr::turnR(float vel)
{
    updatePhase(-(vel * Ts_s_IN_SEC), (vel * Ts_s_IN_SEC));
    
    X = Ffull(t, tc, ts, phiS, phi0);
    XPi = Ffull(t2 + M_PI, tc, ts, phiS, phi0);
    
    float L1 = X;
    float L2 = Ffull(t + M_PI, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
    float R1 = XPi;
    float R2 = Ffull(t2, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
  
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
    float L2 = Ffull(t + M_PI, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
    float R1 = XPi;
    float R2 = Ffull(t2, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
  
    l1(L1);
    l4(R2);
    l5(L1);

    l2(R1);
    l3(L2);
    l6(R1);
}

Orkestr robot;


/*SM TURN


    // float XL = Ffull((t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc, ts + delta_ts, phiS, phi0 + delta_phi0);
    // float XR = Ffull((t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc, ts - delta_ts, phiS, phi0 - delta_phi0);
    // float XLPi = Ffull(t* abs(sgn(vel)), tc, ts + delta_ts, phiS, phi0 + delta_phi0);
    // float XRPi = Ffull(t* abs(sgn(vel)), tc, ts - delta_ts, phiS, phi0 - delta_phi0);

    
    // // LEFT
    // float dphi1 = XL;
    // float dphi3 = XLPi;
    // float dphi5 = XL;
    
    // // RIGHT
    // float dphi2 = XRPi;
    // float dphi4 = XR;
    // float dphi6 = XRPi;
    

*/