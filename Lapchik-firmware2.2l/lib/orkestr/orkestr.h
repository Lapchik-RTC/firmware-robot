#pragma once
#include<Arduino.h>
#include "Encoder.h"
#include "regulatori.h"
#include "obekti.h"
#include "f.h"

int sgn(float in)
{
    if(in > 0) return 1;
    else if(in < 0) return -1;
    else return 0;
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
  void Foo(float vel, float delta_ts = 0.0, float delta_phi0 = 0.0);
  
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
  float t, t2, tc, ts, phiS, phi0 = 0.0, delta_ts, delta_phi0;

  private:

  float X, XPi;
  float X1Rpi = 0.0, X3R = 0.0, X5Rpi = 0.0, X2L = 0.0, X4Lpi = 0.0, X6L = 0.0;

  bool kalibrON1 = 1, kalibrON2 = 1, kalibrON3 = 1, kalibrON4 = 1, kalibrON5 = 1, kalibrON6 = 1;
  uint32_t preKalibrTimer = millis();
  uint32_t calibrTime = millis();
  uint32_t whaitPos = millis();
  
    bool firstCalibr = 1;
    bool endCalibr[6] = {0,0,0,0,0,0};
    uint32_t ladXChange = 0;
    bool endLad = 1;
  void updatePhase(float t_, float t2_);

  void l1(float pos){serv[0].setGoalPos(pos);};
  void l2(float pos){serv[1].setGoalPos(pos);};
  void l3(float pos){serv[2].setGoalPos(pos);};
  void l4(float pos){serv[3].setGoalPos(pos);};
  void l5(float pos){serv[4].setGoalPos(pos);};
  void l6(float pos){serv[5].setGoalPos(pos);};  
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

void Orkestr::Foo(float vel, float delta_ts, float delta_phi0){
    updatePhase(vel * Ts_s_IN_SEC, vel * Ts_s_IN_SEC);
    
    // X = Ffull(t * abs(sgn(vel)), tc - delta_ts, ts, phiS, phi0 - delta_phi0);
    // XPi = Ffull( (t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc + delta_ts, ts, phiS, phi0 + delta_phi0);
    
    //right
    X1Rpi  = Ffull((t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc - delta_ts, ts, phiS, phi0 - delta_phi0);
    X3R    = Ffull( t * abs(sgn(vel)),                             tc - delta_ts, ts, phiS, phi0 - delta_phi0);
    X5Rpi  = Ffull((t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc - delta_ts, ts, phiS, phi0 - delta_phi0);

    //left
    X2L    = Ffull( t * abs(sgn(vel)),                             tc + delta_ts, ts, phiS, phi0 + delta_phi0);
    X4Lpi  = Ffull((t + ( M_PI * abs(sgn(vel)) )) * abs(sgn(vel)), tc + delta_ts, ts, phiS, phi0 + delta_phi0);
    X6L    = Ffull( t * abs(sgn(vel)),                             tc + delta_ts, ts, phiS, phi0 + delta_phi0);

    /*float dphi1 = X;
    float dphi2 = XPi;
    float dphi3 = XPi;
    float dphi4 = X;
    float dphi5 = X;
    float dphi6 = XPi;//*/

    // Serial.print("GPos: " + String(X) + '\t');
    //right
    l1(X1Rpi);
    l4(X4Lpi);   
    l5(X5Rpi);
    
    //left
    l2(X2L);
    l3(X3R);
    l6(X6L);
}

//////////////   Enc   //////////////
void Orkestr::allEncZero()
{
    encod[0].encZero();
    encod[1].encZero();
    encod[2].encZero();
    encod[3].encZero();
    encod[4].encZero();
    encod[5].encZero();
}
//////////////   Pos   //////////////
float* Orkestr::getPos()
{
    float* arrPos = new float[6];   
    arrPos[0] = modc(encod[0].get_phi(), 2.0*M_PI);
    arrPos[1] = modc(encod[1].get_phi(), 2.0*M_PI);
    arrPos[2] = modc(encod[2].get_phi(), 2.0*M_PI);
    arrPos[3] = modc(encod[3].get_phi(), 2.0*M_PI);
    arrPos[4] = modc(encod[4].get_phi(), 2.0*M_PI);    
    arrPos[5] = modc(encod[5].get_phi(), 2.0*M_PI);
    return arrPos;
}

//////////////   Calibr   //////////////
void Orkestr::calibr()
{   
    int pVel = 1.2;
    preKalibrTimer = millis();
    while(millis() - preKalibrTimer < 1700)
    {
        serv[0].setGoalSpeed(pVel);
        serv[1].setGoalSpeed(pVel);
        serv[2].setGoalSpeed(pVel);
        serv[3].setGoalSpeed(pVel);
        serv[4].setGoalSpeed(pVel);
        serv[5].setGoalSpeed(pVel);
        for(int i = 0; i < 6; i++) serv[i].tick();
    }
    // serv[0].setGoalSpeed(pVel);
    // serv[1].setGoalSpeed(pVel);
    // serv[2].setGoalSpeed(pVel);
    // serv[3].setGoalSpeed(pVel);
    // serv[4].setGoalSpeed(pVel);
    // serv[5].setGoalSpeed(pVel);
    
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
            serv[0].setGoalSpeed(velR);
        }
        else
        {
            if(endCalibr[0] == false)
                encod[0].encZero();
            endCalibr[0] = true;
            serv[0].setGoalPos(0);
        }

        ///  dv2  ///
        if(analogRead(CS_PIN_2) < TRIG_CUR_2 && (endCalibr[1] == false))
        {
            serv[1].setGoalSpeed(velL);
        }
        else
        {
            if(endCalibr[1] == false)
                encod[1].encZero();

            endCalibr[1] = true;
            serv[1].setGoalPos(0);
        }

        ///  dv3  ///
        if(analogRead(CS_PIN_3) < TRIG_CUR_3 && (endCalibr[2] == false))
        {
            serv[2].setGoalSpeed(velL*1.5);
        }
        else
        {
            if(endCalibr[2] == false)
                encod[2].encZero();

            endCalibr[2] = true;
            serv[2].setGoalPos(0);
        }

        ///  dv4  ///
        if(analogRead(CS_PIN_4) < TRIG_CUR_4 && (endCalibr[3] == false))
        {
            serv[3].setGoalSpeed(velR);
        }
        else
        {
            if(endCalibr[3] == false)
                encod[3].encZero();

            endCalibr[3] = true;
            serv[3].setGoalPos(0);
        }

        ///  dv5  ///
        if(analogRead(CS_PIN_5) < TRIG_CUR_5 && (endCalibr[4] == false))
        {
            serv[4].setGoalSpeed(velR);
        }
        else
        {
            if(endCalibr[4] == false)
                encod[4].encZero();

            endCalibr[4] = true;
            serv[4].setGoalPos(0);
        }

        ///  dv6  ///
        if(analogRead(CS_PIN_6) < TRIG_CUR_6 && (endCalibr[5] == false))
        {
            serv[5].setGoalSpeed(velL);
        }
        else
        {
            if(endCalibr[5] == false)
                encod[5].encZero();

            endCalibr[5] = true;
            serv[5].setGoalPos(0);
        }
        for(int i = 0; i < 6; i++) serv[i].tick();
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
    encod[0].encZero();
    encod[1].encZero();
    encod[2].encZero();
    encod[3].encZero();
    encod[4].encZero();
    encod[5].encZero();
}

void Orkestr::stendUp2()
{
    float upSpd = 4.0;
    for(int i = 0; i < 6; i++) endCalibr[i] = false;
    calibrTime = millis();
    while
    (
        (( modc(encod[0].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(encod[1].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(encod[2].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(encod[3].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(encod[4].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) ||
        ( modc(encod[5].get_phi(), 2.0*M_PI) <= M_PI/2.0 ) )&&
        ( millis() - calibrTime <  1000)
    )
    {
        if( (modc(encod[0].get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[0] == false) )
            serv[0].setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[0] == false)
                encod[0].encZero();
            endCalibr[0] = 1;
            serv[0].setGoalPos(0);
        }

        if( (modc(encod[1].get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[1] == false) )
            serv[1].setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[1] == false)
                encod[1].encZero();
            endCalibr[1] = 1;
            serv[1].setGoalPos(0);
        }

        if( (modc(encod[2].get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[2] == false) )
            serv[2].setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[2] == false)
                encod[2].encZero();
            endCalibr[2] = 1;
            serv[2].setGoalPos(0);
        }

        if( (modc(encod[3].get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[3] == false) )
            serv[3].setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[3] == false)
                encod[3].encZero();
            serv[3].setGoalPos(0);
            endCalibr[3] = 1;
        }

        if( (modc(encod[4].get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[4] == false) )
            serv[4].setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[4] == false)
                encod[4].encZero();
            serv[4].setGoalPos(0);
            endCalibr[4] = 1;
        }

        if( (modc(encod[5].get_phi(), 2.0*M_PI) <= M_PI/2.0) && (endCalibr[5] == false) )
            serv[5].setGoalSpeed(upSpd);
        else
        {
            if(endCalibr[5] == false)
                encod[5].encZero();
            serv[5].setGoalPos(0);
            endCalibr[5] = 1;
        }
        for(int i = 0; i < 6; i++) serv[i].tick();
    }
    for(int i = 0; i < 6; i++) endCalibr[i] = false;
    serv[0].setGoalPos(0);
    serv[1].setGoalPos(0);
    serv[2].setGoalPos(0);
    serv[3].setGoalPos(0);
    serv[4].setGoalPos(0);
    serv[5].setGoalPos(0);
    for(int i = 0; i < 6; i++) serv[i].tick();
}

void Orkestr::setPhiAll(float nPhiL, float nPhiR)
{
    encod[0].encZero();
    encod[1].encZero();
    encod[2].encZero();
    encod[3].encZero();
    encod[4].encZero();
    encod[5].encZero();

    int _k = -1;
    whaitPos = millis();
    while((millis() - whaitPos < 1500) && (
        (encod[5].get_phi() < nPhiL * 0.8) || (encod[5].get_phi() < (nPhiL  + (nPhiL * 0.2)))
        ||
        (encod[0].get_phi() < nPhiR * 0.8) || (encod[0].get_phi() < (nPhiR  + (nPhiR * 0.2)))
        ||
        (encod[1].get_phi() < nPhiL * 0.8) || (encod[1].get_phi() < (nPhiL  + (nPhiL * 0.2)))
        ||
        (encod[2].get_phi() < nPhiL * 0.8) || (encod[2].get_phi() < (nPhiL  + (nPhiL * 0.2)))
        ||
        (encod[3].get_phi() < nPhiR * 0.8) || (encod[3].get_phi() < (nPhiR  + (nPhiR * 0.2)))
        ||
        (encod[4].get_phi() < nPhiR * 0.8) || (encod[4].get_phi() < (nPhiR  + (nPhiR * 0.2)))
    )
    )
    {
        serv[0].setGoalPos(nPhiR * _k);
        serv[1].setGoalPos(-nPhiL);
        serv[2].setGoalPos(-nPhiL);
        serv[3].setGoalPos(nPhiR * _k);
        serv[4].setGoalPos(nPhiR * _k);
        serv[5].setGoalPos(-nPhiL);
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
       serv[0].setGoalSpeed(-M_PI/6);
       serv[1].setGoalSpeed(-M_PI/6);
       if(!( (millis() - ladXChange >  ((vel * M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 2.0*M_PI)*k_milToS)) ))
       {
           serv[2].setGoalPos(-M_PI/6);
           serv[3].setGoalPos(-M_PI/6);
       }
       l5(X1);
       l6(X1);
    }
    if( (millis() - ladXChange >  ((vel * M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 2.0*M_PI)*k_milToS)) )
    {
       if(! ( millis() - ladXChange <= ((vel * M_PI)*k_milToS) ) && !( (millis() - ladXChange > ((vel * 2.0*M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 3.0*M_PI)*k_milToS)) ))
       {
           serv[0].setGoalPos(-M_PI/6);
           serv[1].setGoalPos(-M_PI/6);
           serv[4].setGoalPos(-M_PI/6);
           serv[5].setGoalPos(-M_PI/6);
       }
       l3(X1);
       l4(X1);
    }
    if( (millis() - ladXChange > ((vel * 2.0*M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 3.0*M_PI)*k_milToS)*0.5) )
    {
       if(!( (millis() - ladXChange >  ((vel * M_PI)*k_milToS)*0.5 ) && (millis() - ladXChange <= ((vel * 2.0*M_PI)*k_milToS)) ))
       {
           serv[2].setGoalPos(-M_PI/6);   
           serv[3].setGoalPos(-M_PI/6);
       }
       serv[4].setGoalPos(-M_PI/6);
       serv[5].setGoalPos(-M_PI/6);
       l1(X1);
       l2(X1);
    }
    if(millis() - ladXChange > ((vel * 3.0*M_PI)*k_milToS)*0.5)
    {   
       serv[0].setGoalPos(-M_PI/6);
       serv[1].setGoalPos(-M_PI/6);
       serv[2].setGoalPos(-M_PI/6);
       serv[3].setGoalPos(-M_PI/6);
       serv[4].setGoalPos(-M_PI/6);
       serv[5].setGoalPos(-M_PI/6);
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