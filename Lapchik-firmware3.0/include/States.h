#pragma once
#include <Arduino.h>
#include "SLOVAR.h"
#include "f.h"
#include "DvigDriver.h"

class State
{
    public:
    State(Dvigatel *dvs[6], void (_work)(Dvigatel*[6], float, float)): dv{}
    {
        for (int i = 0; i < 6; i++) {
            dv[i] = dvs[i];
        }
        this->work = _work;
    }
    void upd(float val, float val2)
    {
        work(dv, val, val2);
    }
    private:
    Dvigatel *dv[6];
    void (*work)(Dvigatel*[6], float, float);
};
////////////////////////////////////////////////////////////////////

void _Foo(Dvigatel*dv[6], float vel, float vel2)
{
    static float t = 0.0, t2 = 0.0, X = 0.0, XPi = 0.0;
    t = vel * Ts_s;
    t2 = vel2 * Ts_s;

    X =   Ffull( ( t + (M_PI * abs( sgn(vel) )) ) * abs(sgn(vel)), TC, TS, PHIS, PHI0);
    XPi = Ffull( t * abs(sgn(vel)),                                TC, TS, PHIS, PHI0);
    dv[0]->setPos(X);
    dv[2]->setPos(X);
    dv[4]->setPos(X);

    dv[1]->setPos(XPi);
    dv[3]->setPos(XPi);   
    dv[5]->setPos(XPi);
}