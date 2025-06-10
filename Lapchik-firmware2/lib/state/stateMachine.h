#pragma once
#include "obekti.h"
#include "orkestr.h"
#include "svyaz.h"
#include "hall.h"

uint32_t lastCalibrTime = millis();
#define TIME_WITHOUT_CALIBR 8000/*6700*/

enum mState
{
    sleep =   0,
    forw =    1,
    turnL =   2,
    s_turnL = 3,
    turnR =   4,
    s_turnR = 5,
    revers =  6,
    calibro = 7,
    synchro = 8,
    a2 =      9

    // psvC = 7,

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
    bool _forw =       1,
         _tLeft =      1,
         _tRight =     1,
         _s_tLeft =    1,
         _s_tRight =   1,
         _back =       1,
         autoGo2 =     1;
    uint32_t timeAuto = 0;

    bool ladm = 0;
    bool sleepCalibr = 0;
    uint32_t timeSC = millis();
    void HallMagic(mState _sm);
};

void StateMachine::HallMagic(mState _sm)
{           
    if(_sm == sleep)
    {         
        for(int i = 0; i < 6; i++)
        {
            if(halls[i].getCondition() == 1)
            {
                timeSC = millis();
                while ( halls[i].getCondition() == 1 && millis() - timeSC < 750)
                {
                    halls[i].myserv->setGoalSpeed(3.0);
                }
                halls[i].myserv->setGoalSpeed(0);
                halls[i].ecn->encZero();
                halls[i].myserv->setGoalPos(0);
            }
        }
    }
}


#define _T_     robot.getRT()
#define _TC_    2.0 * M_PI
#define _TS_    3.6/*2.7*/
#define _PHIS_  0.5
#define _PHI0_  0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void StateMachine::StateMachineUpd()
{
    switch (ChoiseState())
    {
        //------
        case sleep:
            if(sleepCalibr)            {
                HallMagic(state);
                sleepCalibr = 0;
            }
            robot.Foo(0);
            break;

        //------
        case forw:
            if(_forw)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                _forw = 0;
            }
            if(ladmode()) ladm = !ladm;

            // if(ladm == 0)
            // {
            //     robot.ladFoo(spd);
            // }
            // else
            // {
                robot.Foo(spd);
            // }



            
            break;

        //-------------------------------------------------------------------
        case turnL:
            if(_tLeft)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                robot.t2 = _T_;
                _tLeft = 0;
            }

            robot.turnL(spd);
            break;

        //------
        case turnR:
            if(_tRight)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                robot.t2 = _T_;
                _tRight = 0;
            }

            robot.turnR(spd);
            break;
        
        //------
        case s_turnR:
            if(_s_tRight)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                robot.t2 = _T_;
                _s_tRight = 0;
            }

            robot.ShiftTurnR(spd);
            break;
        case s_turnL:
            if(_s_tLeft)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                robot.t2 = _T_;
                _s_tLeft = 0;
            }

            robot.ShiftTurnL(spd);
            break;
        //-------------------------------------------------------------------
        case revers:
            if(_back)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                _back = 0;
            }

            robot.ReversFoo(spd, spd);
            break;
        //------
        // case psvC:
        //     if(psC)
        //     {
        //         // robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
        //         psC = 0;
        //         timeAuto = millis();
        //     }
        //     while(millis() - timeAuto < 5000)
        //     {
                
        //     }
        //     break;
        //------
        case a2:
            if(autoGo2)
            {
                robot.setParams(_T_, _TC_, _TS_, _PHIS_, _PHI0_);
                autoGo2 = 0;
                timeAuto = millis();
            }
            while(millis() - timeAuto < 8000)
            {
                robot.Foo(spd);
            }
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
            _s_tLeft = 1;
            _s_tRight = 1;
            autoGo2 = 1;
            sleepCalibr = 1;

            choised = true;
        }
        /*if(ladmode() && !choised)
        {
            st = psvC;

            _forw = 1;
            _tLeft = 1;
            _tRight = 1;
            _back = 1;
            autoGo2 = 1;
        }*/
        if(delsec_N() && !choised)
        {
            st = a2;

            _forw = 1;
            _tLeft = 1;
            _tRight = 1;
            _back = 1;
            _s_tLeft = 1;
            _s_tRight = 1;
            sleepCalibr = 1;
        }
        if(vpravo() && !choised)
        {
            if(shift())
            {
                st = s_turnR;
            }
            else
            {
                st = turnR;
            }

            _forw = 1;
            _tLeft = 1;
            _back = 1;
            _s_tLeft = 1;
            _s_tRight = 1;
            autoGo2 = 1;
            sleepCalibr = 1;

            choised = true;
        }
        if(vlevo() && !choised)
        {
            if(shift())
            {
                st = s_turnL;
            }
            else
            {
                st = turnL;
            }

            _forw = 1;
            _tRight = 1;
            _back = 1;
            _s_tLeft = 1;
            _s_tRight = 1;
            autoGo2 = 1;
            sleepCalibr = 1;

            choised = true;
        }
        if(nazad() && !choised)
        {
            st = revers;

            _forw = 1;
            _tLeft = 1;
            _tRight = 1;
            _s_tLeft = 1;
            _s_tRight = 1;
            autoGo2 = 1;
            sleepCalibr = 1;

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
            _s_tLeft = 1;
            _s_tRight = 1;
            autoGo2 = 1;
            sleepCalibr = 1;
            
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
        _s_tLeft = 1;
        _s_tRight = 1;
        autoGo2 = 1;
    }
    state = st;
    // Serial.println(st);
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

StateMachine sm;