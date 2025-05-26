#pragma once
#include "obekti.h"
#include "orkestr.h"
#include "svyaz.h"

uint32_t lastCalibrTime = millis();
#define TIME_WITHOUT_CALIBR 10000

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

    private:
    mState state = sleep;
    mState ChoiseState();
    float spd = 3.0;
};

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
            robot.Foo(spd);
            break;

        //------
        case turnL:
            robot.turnL(spd);
            break;

        //------
        case turnR:
            robot.turnR(spd);
            break;

        //------
        case revers:
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
            choised = true;
        }
        if(vlevo() && !choised)
        {
            st = turnL;
            choised = true;
        }
        if(nazad() && !choised)
        {
            st = revers;
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
            lastCalibrTime = millis();
        }
        
    
    }
    else
    {
        st = sleep;
    }
    state = st;
    return st;
}