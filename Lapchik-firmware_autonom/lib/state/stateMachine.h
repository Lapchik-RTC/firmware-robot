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
            //Serial.println("Сплю");
            break;

        //------
        case forw:
            robot.Foo(spd);
            //Serial.println("Вперед");
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
            robot.ostCalibr();
            robot.allEncZero();
            break;

        //------ 
        default:
            break;
    }
}
uint32_t lastCalibrTime = millis();
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
        int timeWithoutCalibr = 3000;
        if(calibr() && !choised && (millis() - lastCalibrTime > timeWithoutCalibr))
        {
            st = calibro;
            choised = true;
            lastCalibrTime = millis();
        }
        if(st == calibro && (millis() - lastCalibrTime > timeWithoutCalibr))
        {
            st = sleep;
        }
    
    }
    else
    {
        st = sleep;
    }
    state = st;
    return st;
}