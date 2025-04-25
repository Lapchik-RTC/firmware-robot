#pragma once
#include<Arduino.h>

#include "orkestr.h"
class StatesPassport
{
    public:
    void (*func)();
    String name;
    int num;
};

class SubStateMachine
{
    public:

    void addState(void (*func)(), String name);
    void setState(String name);
    int controlDriver();
    void changeState();
    SubStateMachine(){void setDefaultStates();}
    private:
    StatesPassport* dynamicStateArr = new StatesPassport[4];
    void setDefaultStates();
    int i = 0;
};