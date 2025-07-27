#pragma once
#include "MotorDriver.h"
#include "Obj.h"



////////////////////////////////////////////////////////////////////
//
////////////////////////     TRIPOD     ////////////////////////////
//
////////////////////////////////////////////////////////////////////
class Tripod
{
    private:
    Motor *m1, *m2, *m3;

    public:
    Tripod(Motor* _m1, Motor* _m2, Motor* _m3)
    : m1(_m1), m2(_m2), m3(_m3){}

    void setSpeed(float gSpd);
    void setPos(float gAng);
    void tick();
};

void Tripod::setSpeed(float gSpd)
{
    m1->setSpeed(gSpd);
    m2->setSpeed(gSpd);
    m3->setSpeed(gSpd);
}

void Tripod::setPos(float gAng)
{
    m1->setPos(gAng);
    m2->setPos(gAng);
    m3->setPos(gAng);
}

void Tripod::tick()
{
    m1->tick();
    m2->tick();
    m3->tick();
}



////////////////////////////////////////////////////////////////////
//
////////////////////////      PAIR      ////////////////////////////
//
////////////////////////////////////////////////////////////////////
class Duopod
{
    private:
    Motor *m1, *m2;

    public:
    Duopod(Motor* _m1, Motor* _m2)
    : m1(_m1), m2(_m2){}

    void setSpeed(float gSpd);
    void setPos(float gAng);
    void tick();
};

void Duopod::setSpeed(float gSpd)
{
    m1->setSpeed(gSpd);
    m2->setSpeed(gSpd);
}

void Duopod::setPos(float gAng)
{
    m1->setPos(gAng);
    m2->setPos(gAng);
}

void Duopod::tick()
{
    m1->tick();
    m2->tick();
}



////////////////////////////////////////////////////////////////////
//
////////////////////////     HEXAPOD     ///////////////////////////
//
////////////////////////////////////////////////////////////////////
// class Hexapod
// {
//     public:
//     void setSpeed(float gSpd);
//     void setPos(float gAng);
//     void tick();
// };

// void Hexapod::setSpeed(float gSpd)
// {
//     Serv[0].setSpeed(gSpd);
//     Serv[1].setSpeed(gSpd);
//     Serv[2].setSpeed(gSpd);
//     Serv[3].setSpeed(gSpd);
//     Serv[4].setSpeed(gSpd);
//     Serv[5].setSpeed(gSpd);
// }

// void Hexapod::setPos(float gAng)
// {
//     Serv[0].setPos(gAng);
//     Serv[1].setPos(gAng);
//     Serv[2].setPos(gAng);
//     Serv[3].setPos(gAng);
//     Serv[4].setPos(gAng);
//     Serv[5].setPos(gAng);
// }

// void Hexapod::tick()
// {
//     Serv[0].tick();
//     Serv[1].tick();
//     Serv[2].tick();
//     Serv[3].tick();
//     Serv[4].tick();
//     Serv[5].tick();
// }