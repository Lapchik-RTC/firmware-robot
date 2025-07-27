#pragma once
#include <Arduino.h>
#include "Obj.h"


class RHex
{
    private:
    
    float t = 0.0, tc = 0.0, ts = 0.0, phiS = 0.0, phi0 = 0.0, delta_ts = 0.0, delta_phi0 = 0.0;
    float X = 0.0, Xpi = 0.0;

    enum RHEX_CONTROL_MODE
    {
        TRIPOD_MODE,
        DUO_MODE,
        HEXA_MODE
    };
    RHEX_CONTROL_MODE controlMode = TRIPOD_MODE;

    public:
    void setParams(float _t, float _tc, float _ts, float _phiS, float _phi0, float _delta_ts, float _delta_phi0);
    void ClassicWalk(float lineVel, float anglWel);
    void tick();
};

void RHex::ClassicWalk(float lineVel, float anglWel = 0.0)
{
    controlMode = TRIPOD_MODE;
    t += lineVel*Ts_s;
    X = Ffull(t, tc, ts, phiS, phi0);
    Xpi = Ffull((t + M_PI), tc, ts, phiS, phi0);

    trpL.setPos(X);
    trpR.setPos(Xpi); 
}

void RHex::setParams(float _t, float _tc, float _ts, float _phiS, float _phi0, float _delta_ts = 0, float _delta_phi0 = 0.0)
{
    this->t = _t;
    this->tc = _tc;
    this->ts = _ts;
    this->phiS = _phiS;
    this->phi0 = _phi0;
    this->delta_ts = _delta_ts;
    this->delta_phi0 = _delta_phi0;
}

void RHex::tick()
{
    if(controlMode == TRIPOD_MODE)
    {
        trpL.tick();
        trpR.tick();
    }
}