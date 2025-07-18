#include <Arduino.h>
#include "Parameters.h"
#include "Obj.h"
#include "f.h"
#include "softCheck.h"

void setup() {
    Serial.begin(115200);

}

// void setParams(float t_, float tc_, float ts_, float phiS_, float phi0_, float delta_ts_ = 0.0, float delta_phi0_ = 0.0)
// {
//     this->t = t_;
//     this->t2 = t_;
//     this->tc = tc_;
//     this->ts = ts_;
//     this->phiS = phiS_;
//     this->phi0 = phi0_;
//     this->delta_ts = delta_ts_;
//     this->delta_phi0 = delta_phi0_;
// }

// void updatePhase(float t_, float t2_ = 0.0)
// {
//     this->t += t_;
//     // this->t2 += t2_;
// }
float t = 0.0;
void Foo(float speed)
{
    // updatePhase(speed * Ts_s);
    t += speed*Ts_s;
    float X = Ffull( t, 2.0*M_PI, 3.9, 0.5, 0.0);
    
    // if((Serv[3].getAngle()/M_PI) > 5.0)
    // {
    //     while(1)
    //     {
    //         Serv[3].setPos(t);
    //         Serv[3].tick();
    //     }
    // }
    Serial.println(Serv[3].getAngle());
    Serv[3].setPos(X);
}

void loop() {
    static uint64_t timer = micros();
    while(micros() - timer < Ts_us);
    timer = micros();
    // SpeedRegSens_R_F_pers(3);
    Foo(3.0);

    // static float testPos = 0.0;
    // if(testPos < 10.0*M_PI)
    // {
    //     testPos+=0.01;
    //     Serv[3].setPos(testPos);
    // }
    // else
    // {
    //     Serv[3].setPos(testPos);
    // }
    // Serial.println(String(Serv[3].getEnc()) + "   " + String(testPos) + "   " + String(Serv[3].getAngle()));

    Serv[3].tick();
}
