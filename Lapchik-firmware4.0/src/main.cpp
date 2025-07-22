#include <Arduino.h>
#include "Parameters.h"
#include "Obj.h"
#include "f.h"
#include "softCheck.h"
#include "Pods.h"
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
    
    
    Serv[3].setPos(X);
    Serv[5].setPos(X);
}

void StendUp()
{
    uint32_t time_stendup = millis();
    float dPos = M_PI*0.5;
    while(millis() - time_stendup < 1500)
    {
        static bool ir[6] = {0,0,0,0,0,0};
        for(int i = 0; i < 6; i++)
        {
            if(Serv[i].getAngle() > dPos+0.5 || Serv[i].getAngle() < dPos-0.5)
                Serv[i].setPos(dPos);
            else
            {
                if(!ir[i])
                {
                    Serv[i].zeroEnc();
                    ir[i] = 1;
                }
                Serv[i].setPos(0.0);
            }
            Serv[i].tick();
        }
    }

}


Tripod trpL(&Serv[1], &Serv[2], &Serv[5]);
Tripod trpR(&Serv[0], &Serv[3], &Serv[4]);
float X = 0.0, Xpi = 0.0;

void loop() {
    static uint64_t timer = micros();
    while(micros() - timer < Ts_us);
    timer = micros();

    float spd = 3.0;

    StendUp();
    while(1);
    

    /*t += spd*Ts_s;
    X = Ffull( t, 2.0*M_PI, 3.9, 0.5, 0.0);
    Xpi = Ffull( t + M_PI, 2.0*M_PI, 3.9, 0.5, 0.0);

    trpL.setPos(X);
    trpR.setPos(Xpi); 

    trpL.tick();
    trpR.tick();*/

}
