#pragma once

#include "Servo.h"
#include "Globals.h"

class Orchestrator
{
private:
    float t; // phase

    Servo *s1, *s2, *s3, *s4, *s5, *s6;

    float v_f0, theta_i0;

    float F(float t, float tttt /*.....*/);
public:

    Orchestrator(Servo *s1_, Servo  *s2_, Servo  *s3_, Servo  *s4_, Servo  *s5_, Servo  *s6_)
    {
        s1 = s1_;
        s2 = s2_;
        s3 = s3_;
        s4 = s4_;
        s5 = s5_;
        s6 = s6_;
    }

    void
};