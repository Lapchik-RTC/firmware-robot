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
  void stendUp2();
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
  float t, t2, tc, ts, phiS, phi0;

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

  void l1(float pos){serv1.setGoalPos(pos);};
  void l2(float pos){serv2.setGoalPos(pos);};
  void l3(float pos){serv3.setGoalPos(pos);};
  void l4(float pos){serv4.setGoalPos(pos);};
  void l5(float pos){serv5.setGoalPos(pos);};
  void l6(float pos){serv6.setGoalPos(pos);};  
};

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////   Foo   //////////////
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

    XPi = Ffull(t * abs(sgn(vel)), tc, ts, phiS, phi0/* + ((M_PI/6.0)* abs(sgn(vel)))*/);
    X = Ffull( (t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc, ts, phiS, phi0);
    // XPi = X;
    float dphi1 = X;
    float dphi2 = XPi;
    float dphi3 = XPi;
    float dphi4 = X;
    float dphi5 = X;
    float dphi6 = XPi;

    // Serial.print("GPos: " + String(X) + '\t');

    l3(dphi3);
    l5(dphi5);
    l1(dphi1);
    l4(dphi4);
    l2(dphi2);
    l6(dphi6);
}

//////////////   Enc   //////////////
void Orkestr::allEncZero()
{
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
}
//////////////   Pos   //////////////
float* Orkestr::getPos()
{
    float* arrPos = new float[6];   
    arrPos[0] = modc(enc_1.get_phi(), 2.0*M_PI);
    arrPos[1] = modc(enc_2.get_phi(), 2.0*M_PI);
    arrPos[2] = modc(enc_3.get_phi(), 2.0*M_PI);
    arrPos[3] = modc(enc_4.get_phi(), 2.0*M_PI);
    arrPos[4] = modc(enc_5.get_phi(), 2.0*M_PI);    
    arrPos[5] = modc(enc_6.get_phi(), 2.0*M_PI);
    return arrPos;
}

//////////////   Calibr   //////////////
void Orkestr::calibr()
{   
    // if(firstCalibr)
    // {
        int pVel = 1.2;
        preKalibrTimer = millis();
        while(millis() - preKalibrTimer < 1700)
        {
            serv1.setGoalSpeed(pVel);
            serv2.setGoalSpeed(pVel);
            serv3.setGoalSpeed(pVel);
            serv4.setGoalSpeed(pVel);
            serv5.setGoalSpeed(pVel);
            serv6.setGoalSpeed(pVel);
        }
        serv1.setGoalSpeed(pVel);
        serv2.setGoalSpeed(pVel);
        serv3.setGoalSpeed(pVel);
        serv4.setGoalSpeed(pVel);
        serv5.setGoalSpeed(pVel);
        serv6.setGoalSpeed(pVel);
       // firstCalibr = 0;
    /*}
    else
    {
        if(firstCalibr == 0){

            preKalibrTimer = millis();
            while(millis() - preKalibrTimer < 1000)
            {
                float antVel = -1.0;
                serv1.setGoalSpeed(antVel);
                serv2.setGoalSpeed(antVel);
                serv3.setGoalSpeed(antVel);
                serv4.setGoalSpeed(antVel);
                serv5.setGoalSpeed(antVel);
                serv6.setGoalSpeed(antVel);
            }
            preKalibrTimer = millis();
            while(millis() - preKalibrTimer < 600)
            {
                serv1.setGoalPos(M_PI);
                serv2.setGoalPos(M_PI);
                serv3.setGoalPos(M_PI);
                serv4.setGoalPos(M_PI);
                serv5.setGoalPos(M_PI);
                serv6.setGoalPos(M_PI);
            }

            preKalibrTimer = millis();
            while(millis() - preKalibrTimer < 300)
            {
                float antVel = 1.0;
                serv1.setGoalSpeed(antVel);
                serv2.setGoalSpeed(antVel);
                serv3.setGoalSpeed(antVel);
                serv4.setGoalSpeed(antVel);
                serv5.setGoalSpeed(antVel);
                serv6.setGoalSpeed(antVel);
            }
        }
    }*/
    
    float velL = 3.0, velR = velL;
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
        ///  dv1  ///
        if(analogRead(CS_PIN_1) < TRIG_CUR_1 && (endCalibr[0] == false))
        {
            serv1.setGoalSpeed(velR);
        }
        else
        {
            if(endCalibr[0] == false)
                enc_1.encZero();
            endCalibr[0] = true;
            serv1.setGoalPos(0);
        }

        ///  dv2  ///
        if(analogRead(CS_PIN_2) < TRIG_CUR_2 && (endCalibr[1] == false))
        {
            serv2.setGoalSpeed(velL);
        }
        else
        {
            if(endCalibr[1] == false)
                enc_2.encZero();

            endCalibr[1] = true;
            serv2.setGoalPos(0);
        }

        ///  dv3  ///
        if(analogRead(CS_PIN_3) < TRIG_CUR_3 && (endCalibr[2] == false))
        {
            serv3.setGoalSpeed(velL*1.5);
        }
        else
        {
            if(endCalibr[2] == false)
                enc_3.encZero();

            endCalibr[2] = true;
            serv3.setGoalPos(0);
        }

        ///  dv4  ///
        if(analogRead(CS_PIN_4) < TRIG_CUR_4 && (endCalibr[3] == false))
        {
            serv4.setGoalSpeed(velR);
        }
        else
        {
            if(endCalibr[3] == false)
                enc_4.encZero();

            endCalibr[3] = true;
            serv4.setGoalPos(0);
        }

        ///  dv5  ///
        if(analogRead(CS_PIN_5) < TRIG_CUR_5 && (endCalibr[4] == false))
        {
            serv5.setGoalSpeed(velR);
        }
        else
        {
            if(endCalibr[4] == false)
                enc_5.encZero();

            endCalibr[4] = true;
            serv5.setGoalPos(0);
        }

        ///  dv6  ///
        if(analogRead(CS_PIN_6) < TRIG_CUR_6 && (endCalibr[5] == false))
        {
            serv6.setGoalSpeed(velL);
        }
        else
        {
            if(endCalibr[5] == false)
                enc_6.encZero();

            endCalibr[5] = true;
            serv6.setGoalPos(0);
        }
    }
    for(int i = 0; i < 6; i++) endCalibr[i] = false;


    ////////////////////
    //while (1); 
    ////////////////////

    allEncZero();
    stendUp2();
    allEncZero();
}

void Orkestr::stendUp()
{
    float startPos = M_PI*1.5;// + (M_PI/2.0) + (M_PI/30.0);
    setPhiAll(startPos, startPos);
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
}

void Orkestr::stendUp2()
{
    float upSpd = 4.0;
    for(int i = 0; i < 6; i++) endCalibr[i] = false;
    calibrTime = millis();
    while
    (
        (( modc(enc_1.get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(enc_2.get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(enc_3.get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(enc_4.get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(enc_5.get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(enc_6.get_phi(), 2.0*M_PI) <= M_PI/2.0 ) )&&
        ( millis() - calibrTime <  1000)
    )
    {
        if( (modc(enc_1.get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[0] == false) )
            serv1.setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[0] == false)
                enc_1.encZero();
            endCalibr[0] = 1;
            serv1.setGoalPos(0);
        }

        if( (modc(enc_2.get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[1] == false) )
            serv2.setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[1] == false)
                enc_2.encZero();
            endCalibr[1] = 1;
            serv2.setGoalPos(0);
        }

        if( (modc(enc_3.get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[2] == false) )
            serv3.setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[2] == false)
                enc_3.encZero();
            endCalibr[2] = 1;
            serv3.setGoalPos(0);
        }

        if( (modc(enc_4.get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[3] == false) )
            serv4.setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[3] == false)
                enc_4.encZero();
            serv4.setGoalPos(0);
            endCalibr[3] = 1;
        }

        if( (modc(enc_5.get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[4] == false) )
            serv5.setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[4] == false)
                enc_5.encZero();
            serv5.setGoalPos(0);
            endCalibr[4] = 1;
        }

        if( (modc(enc_6.get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[5] == false) )
            serv6.setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[5] == false)
                enc_6.encZero();
            serv6.setGoalPos(0);
            endCalibr[5] = 1;
        }
    }
    for(int i = 0; i < 6; i++) endCalibr[i] = false;
    serv1.setGoalPos(0);
    serv2.setGoalPos(0);
    serv3.setGoalPos(0);
    serv4.setGoalPos(0);
    serv5.setGoalPos(0);
    serv6.setGoalPos(0);    
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
        serv2.setGoalPos(-nPhiL);
        serv3.setGoalPos(-nPhiL);
        serv4.setGoalPos(nPhiR * _k);
        serv5.setGoalPos(nPhiR * _k);
        serv6.setGoalPos(-nPhiL);
    }
}

/////////////////////////////////////////////

//////////////   Other move   //////////////

/////////////////////////////////////////////

void Orkestr::ladFoo(float vel)
{
    updatePhase((vel * Ts_s_IN_SEC), (vel * Ts_s_IN_SEC));

    X1 = Ffull(t, 2.0*M_PI, 1.3, 1.3, 0);    

    if(endLad)
    {
       ladXChange = millis();
       endLad = 0;
    }
    int k_milToS = 100;
    
    if( millis() - ladXChange <= ((vel * M_PI)*k_milToS) )
    {
       serv1.setGoalSpeed(-M_PI/6);
       serv2.setGoalSpeed(-M_PI/6);
       if(!( (millis() - ladXChange >  ((vel * M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 2.0*M_PI)*k_milToS)) ))
       {
           serv3.setGoalPos(-M_PI/6);
           serv4.setGoalPos(-M_PI/6);
       }
       l5(X1);
       l6(X1);
    }
    if( (millis() - ladXChange >  ((vel * M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 2.0*M_PI)*k_milToS)) )
    {
       if(! ( millis() - ladXChange <= ((vel * M_PI)*k_milToS) ) && !( (millis() - ladXChange > ((vel * 2.0*M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 3.0*M_PI)*k_milToS)) ))
       {
           serv1.setGoalPos(-M_PI/6);
           serv2.setGoalPos(-M_PI/6);
           serv5.setGoalPos(-M_PI/6);
           serv6.setGoalPos(-M_PI/6);
       }
       l3(X1);
       l4(X1);
    }
    if( (millis() - ladXChange > ((vel * 2.0*M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 3.0*M_PI)*k_milToS)*0.5) )
    {
       if(!( (millis() - ladXChange >  ((vel * M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 2.0*M_PI)*k_milToS)) ))
       {
           serv3.setGoalPos(-M_PI/6);   
           serv4.setGoalPos(-M_PI/6);
       }
       serv5.setGoalPos(-M_PI/6);
       serv6.setGoalPos(-M_PI/6);
       l1(X1);
       l2(X1);
    }
    if(millis() - ladXChange > ((vel * 3.0*M_PI)*k_milToS)*0.5)
    {   
       serv1.setGoalPos(-M_PI/6);
       serv2.setGoalPos(-M_PI/6);
       serv3.setGoalPos(-M_PI/6);
       serv4.setGoalPos(-M_PI/6);
       serv5.setGoalPos(-M_PI/6);
       serv6.setGoalPos(-M_PI/6);
       endLad = 1;
    }
    
}



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
/////////////////////////////////////////////

//////////////   SHIFT MODE   ///////////////

/////////////////////////////////////////////
void Orkestr::ShiftTurnR(float vel)
{
    updatePhase(-(vel * Ts_s_IN_SEC), (vel * Ts_s_IN_SEC));
    
    X = Ffull( 0, tc, ts, phiS, phi0);

    float _L = Ffull(t + M_PI, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
    float _R = Ffull(t2, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
  
    l4(_R);
    l3(_L);

    l1(X);
    l5(X);
    l2(X);
    l6(X);

}

void Orkestr::ShiftTurnL(float vel)
{
    updatePhase((vel * Ts_s_IN_SEC), -(vel * Ts_s_IN_SEC));
    
    X = Ffull( 0, tc, ts, phiS, phi0);

    float _L = Ffull(t + M_PI, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
    float _R = Ffull(t2, tc, ts, phiS, phi0/*+(M_PI/6.0)*/);
  
    l4(_R);
    l3(_L);

    l1(X);
    l5(X);
    l2(X);
    l6(X);

}

Orkestr robot;