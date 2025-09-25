#pragma once
#include "SLOVAR.h"
#include "obekti.h"

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
    
    private:
    byte pin;
};

Hall halls[6] = 
{
    Hall(HALL_PIN_1, &serv[0], &encod[0], 1), 
    Hall(HALL_PIN_2, &serv[1], &encod[1], 1), 
    Hall(HALL_PIN_3, &serv[2], &encod[2]), 
    Hall(HALL_PIN_4, &serv[3], &encod[3]), 
    Hall(HALL_PIN_5, &serv[4], &encod[4]), 
    Hall(HALL_PIN_6, &serv[5], &encod[5])
};