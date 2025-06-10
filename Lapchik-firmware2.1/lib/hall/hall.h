#pragma once
#include "SLOVAR.h"
// #include "obekti.h"

// ServoPrivod* priv[6]

class Hall
{
    public:
    Encoder* ecn;
    ServoPrivod* myserv;
    bool mirr = 0;

    Hall(byte pin, ServoPrivod* msv, Encoder* ecn, bool mirr = 0):myserv(msv), ecn(ecn)
    {
        this -> pin = pin;
        pinMode(this->pin, 0);
        this->mirr = mirr;
    }
    bool getCondition(){return digitalRead(pin);}
    byte getPin(){return pin;}
    private:
    byte pin;
};

Hall halls[6] = 
{
    Hall(hallPin[0], &privod[0], &Enc[0]),
    Hall(hallPin[1], &privod[1], &Enc[1]),
    Hall(hallPin[2], &privod[2], &Enc[2]),
    Hall(hallPin[3], &privod[3], &Enc[3]),
    Hall(hallPin[4], &privod[4], &Enc[4]),
    Hall(hallPin[5], &privod[5], &Enc[5])
};
// void HInit()
// {
//     for(int i = 0; i < 6; i++)
//     {
//         halls[i] = Hall(hallPin[i], &privod[i], &Enc[i]);
//     }
// }