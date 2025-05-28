#pragma once
#include "obekti.h"

class Hall
{
    public:
    void Init();
    void Upd();

    private:
    uint32_t timeHall[6] = {0,0,0,0,0,0};
    float spd = 0.5;

};

void Hall::Init()
{
    //DDRD &= ~(1 << PD2);
    pinMode(HALL_PIN_1, INPUT);
    pinMode(HALL_PIN_2, INPUT);
    pinMode(HALL_PIN_3, INPUT);
    pinMode(HALL_PIN_4, INPUT);
    pinMode(HALL_PIN_5, INPUT);
    pinMode(HALL_PIN_6, INPUT);
    for(int i = 0; i < 6; i++) timeHall[i] = millis();
}

void Hall::Upd()
{
    //if (PIND & (1 << PD2))
    float luftUst = M_PI/12.0;
    float k = 1.5;
    float hallPing = (luftUst/spd)*k;
    bool hallCondition[6] = {
        digitalRead(HALL_PIN_1), 
        digitalRead(HALL_PIN_2), 
        digitalRead(HALL_PIN_3), 
        digitalRead(HALL_PIN_4), 
        digitalRead(HALL_PIN_5), 
        digitalRead(HALL_PIN_6)
    };

    if( !hallCondition[0] && (millis() - timeHall[0] > hallPing) ) {enc_1.encZero(); timeHall[0] = millis();}
    if( !hallCondition[1] && (millis() - timeHall[1] > hallPing) ) {enc_2.encZero(); timeHall[1] = millis();}
    if( !hallCondition[2] && (millis() - timeHall[2] > hallPing) ) {enc_3.encZero(); timeHall[2] = millis();}
    if( !hallCondition[3] && (millis() - timeHall[3] > hallPing) ) {enc_4.encZero(); timeHall[3] = millis();}
    if( !hallCondition[4] && (millis() - timeHall[4] > hallPing) ) {enc_5.encZero(); timeHall[4] = millis();}
    if( !hallCondition[5] && (millis() - timeHall[5] > hallPing) ) {enc_6.encZero(); timeHall[5] = millis();}
}

//////unused
// && (abs( modc(enc_1.get_phi(), 2.0*M_PI) ) < luftUst) 
// && (abs( modc(enc_2.get_phi(), 2.0*M_PI) ) < luftUst) 
// && (abs( modc(enc_3.get_phi(), 2.0*M_PI) ) < luftUst) 
// && (abs( modc(enc_4.get_phi(), 2.0*M_PI) ) < luftUst) 
// && (abs( modc(enc_5.get_phi(), 2.0*M_PI) ) < (luftUst + M_PI))
// && (abs( modc(enc_6.get_phi(), 2.0*M_PI) ) < (luftUst + M_PI))