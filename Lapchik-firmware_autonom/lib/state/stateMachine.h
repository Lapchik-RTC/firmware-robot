#pragma once
#include "obekti.h"
#include "orkestr.h"
#include "svyaz.h"

enum mState
{
    sleep = 0,
    forw = 1,
    turnL = 2,
    turnR = 3,
    revers = 4,
    calibr = 5,

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
        case calibr:
            robot.ostCalibr();
            break;

        //------ 
        default:
            robot.Foo(0);
            break;
    }
}

mState StateMachine::ChoiseState()
{
    if(nado_rabotat())
    {
        bool choised = false;
        if(vpered() && !choised)
        {
            state = forw;
            choised = true;
        }
        if(vperedVmeste() && !choised)
        {
            state = synchro;
            choised = true;
        }
        if(vpravo() && !choised)
        {
            state = turnR;
            choised = true;
        }
        if(vlevo() && !choised)
        {
            state = turnL;
            choised = true;
        }
        if(nazad() && !choised)
        {
            state = revers;
            choised = true;
        }
    }
    else
    {
        state = sleep;
    }
}