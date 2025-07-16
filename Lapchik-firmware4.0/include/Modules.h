#pragma once
#include "f.h"
#include "MotorDriver.h"
#include "Obj.h"

class Tripod: public Motor
{
    private:
    Motor *m1, *m2, *m3;

    public:
    Tripod(Motor *_m1, Motor *_m2, Motor *_m3)
    {
        this->m1 = _m1;
        this->m2 = _m2;
        this->m3 = _m3;
    }
    void setPos();
    void setSpeed();
    void tick();
};
