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
    Hall(HALL_PIN_1, &serv1, &enc_1, 1), 
    Hall(HALL_PIN_2, &serv2, &enc_2, 1), 
    Hall(HALL_PIN_3, &serv3, &enc_3), 
    Hall(HALL_PIN_4, &serv4, &enc_4), 
    Hall(HALL_PIN_5, &serv5, &enc_5), 
    Hall(HALL_PIN_6, &serv6, &enc_6)
};