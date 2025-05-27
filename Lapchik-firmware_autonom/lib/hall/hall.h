#pragma once
#include "obekti.h"

class Hall
{
    public:
    void Init();
    void Upd();
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
}

void Hall::Upd()
{
    //if (PIND & (1 << PD2))
    float* pos = robot.getPos();
    
    float luftUst = M_PI/6.0;

    bool hallCondition[] = {
        digitalRead(HALL_PIN_1), 
        digitalRead(HALL_PIN_2), 
        digitalRead(HALL_PIN_3), 
        digitalRead(HALL_PIN_4), 
        digitalRead(HALL_PIN_5), 
        digitalRead(HALL_PIN_6)
    };
    if( hallCondition[0] && ( abs(pos[0]) < luftUst ) ) enc_1.encZero();
    if( hallCondition[1] && ( abs(pos[1]) < luftUst ) ) enc_2.encZero();
    if( hallCondition[2] && ( abs(pos[2]) < luftUst ) ) enc_3.encZero();
    if( hallCondition[3] && ( abs(pos[3]) < luftUst ) ) enc_4.encZero();
    if( hallCondition[4] && ( abs(pos[4]) < (luftUst + M_PI) ) ) enc_5.encZero();
    if( hallCondition[5] && ( abs(pos[5]) < (luftUst + M_PI) ) ) enc_6.encZero();

    delete[] pos;
}