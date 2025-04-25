#include "subStateMachine.h"

void SubStateMachine::addState(void (*func_)(), String name_)
{

    dynamicStateArr[i] = {func_, name_, i};
    i++;
}

void SubStateMachine::setState(String name)
{
    int j = 0;
    int ex = 1;
    while (ex || (j < i))
    {
        if(dynamicStateArr[j].name == name)
        {
            ex = 0;
            dynamicStateArr[j].func();
        }
        j++;
    }
    j = 0;
    ex = 1;
}

void SubStateMachine::setDefaultStates()
{
    
    // addState(&robot.Foo(4.0), "myFunc");
    // addState(&foo2, "myFunc2");
}

int SubStateMachine::controlDriver()
{
    int a = 0;
    return a;
}

void SubStateMachine::changeState()
{
    setDefaultStates();
    switch(controlDriver())
    {
        case 1:
            
            break;
        default:
            break;
    }
}