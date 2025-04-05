#pragma once
#include "svyaz.h"
Orkestr robot;
void stateMachine()
{
    if(nado_rabotat())
    {
        if(vpered())
        {
            robot.Foo(4.5);
        }
        if(vpravo)
        {
            robot.turnR(4.5);
        }
    }
    else
    {
        // robot.ostCalibr();
        statPosUpd();
        while(!nado_rabotat())
        {
            serv2.setGoalPos(posStatic[1]);
            serv3.setGoalPos(posStatic[2]);
            serv6.setGoalPos(posStatic[5]);  
            serv1.setGoalPos(posStatic[0]);
            serv4.setGoalPos(posStatic[3]);
            serv5.setGoalPos(posStatic[4]);
        }
    }
}