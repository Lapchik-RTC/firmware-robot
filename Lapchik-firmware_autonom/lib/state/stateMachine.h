#pragma once
#include "obekti.h"
#include "orkestr.h"
#include "svyaz.h"

uint32_t lastCalibrTime = millis();
#define TIME_WITHOUT_CALIBR 6700

enum mState
{
    sleep = 0,
    forw = 1,
    turnL = 2,
    turnR = 3,
    revers = 4,
    calibro = 5,

    synchro = 6
};

class StateMachine
{
    public:
    void StateMachineUpd();
    mState getState(){return state;}
    void setSpd(float spd){this->spd = spd;}
    void preState();

    private:
    mState state = sleep;
    mState ChoiseState();
    float spd = 3.0;
    bool _forw = 1, _tLeft = 1, _tRight = 1, _back = 1;
};
#define _T_     0
#define _TC_    2.0 * M_PI
#define _TS_    3.6/*2.7*/
#define _PHIS_  0.5
#define _PHI0_  0

void StateMachine::StateMachineUpd()
{
    switch (ChoiseState())
    {
        //------
        case sleep:
            robot.Foo(0);
            break;

        //------
        case forw:
            if(_forw)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                _forw = 0;
            }

            robot.Foo(spd);
            break;

        //------
        case turnL:
            if(_tLeft)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                _tLeft = 0;
            }

            robot.turnL(spd);
            break;

        //------
        case turnR:
            if(_tRight)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                _tRight = 0;
            }

            robot.turnR(spd);
            break;

        //------
        case revers:
            if(_back)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                _back = 0;
            }

            robot.ReversFoo(spd, spd);
            break;

        //------
        case calibro:
            robot.calibr();
            robot.allEncZero();
            break;

        //------ 
        default:
            break;
    }
}

mState StateMachine::ChoiseState()
{
    mState st = sleep;
    if(nado_rabotat())
    {
        bool choised = false;
        if(vpered() && !choised)
        {
            st = forw;

            _tLeft = 1;
            _tRight = 1;
            _back = 1;

            choised = true;
        }
        // if(vperedVmeste() && !choised)
        // {
        //     st = synchro;
        //     choised = true;
        // }
        if(vpravo() && !choised)
        {
            st = turnR;

            _forw = 1;
            _tLeft = 1;
            _back = 1;

            choised = true;
        }
        if(vlevo() && !choised)
        {
            st = turnL;

            _forw = 1;
            _tRight = 1;
            _back = 1;

            choised = true;
        }
        if(nazad() && !choised)
        {
            st = revers;

            _forw = 1;
            _tLeft = 1;
            _tRight = 1;

            choised = true;
        }
        
        if(st == calibro && (millis() - lastCalibrTime < TIME_WITHOUT_CALIBR))
        {
            st = sleep;
        }

        if(calibr() && !choised && (millis() - lastCalibrTime > TIME_WITHOUT_CALIBR))
        {
            st = calibro;
            choised = true;

            _forw = 1;
            _tLeft = 1;
            _tRight = 1;
            _back = 1;
            
            lastCalibrTime = millis();
        }
        
    
    }
    else
    {
        st = sleep;
        _forw = 1;
        _tLeft = 1;
        _tRight = 1;
        _back = 1;
    }
    state = st;
    Serial.println(st);
    return st;
}

void StateMachine::preState()
{
    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
    robot.calibr();
}