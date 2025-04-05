#pragma once
#include "svyaz.h"
Orkestr robot;
uint32_t pereriv = millis();
uint32_t pererivOst = millis();

void stateMachine()
{
    if(nado_rabotat())
    {
        Serial.print("rabotau");
        if(vpered())
        {
            // while(vpered())
            // {
                Serial.print("vpered");
                // robot.Foo(4.5);
            // }
        }
        if(vpravo())
        {
            Serial.print("vpravo");
            // robot.turnR(4.5);
        }
        if(vlevo())
        {
            Serial.print("vlevo");
            // robot.turnL(4.5);
        }
        if(rovnaysa() && (millis() - pereriv > 1000))
        {
            Serial.print("rovnayas");
            // robot.ostCalibr();
            pereriv = millis();
        }
    }
    else
    {
        // robot.ostCalibr();
        // serv2.setGoalSpeed(0);
        // serv3.setGoalSpeed(0);
        // serv6.setGoalSpeed(0);  
        // serv1.setGoalSpeed(0);
        // serv4.setGoalSpeed(0);
        // serv5.setGoalSpeed(0);
        statPosUpd();
        pererivOst = millis();
        Serial.print("dumau");
        while(!nado_rabotat() && (millis() - pererivOst < 500))
        {
            Serial.println  ("dolgo dumau");
            // serv2.setGoalPos(posStatic[1]);
            // serv3.setGoalPos(posStatic[2]);
            // serv6.setGoalPos(posStatic[5]);  
            // serv1.setGoalPos(posStatic[0]);
            // serv4.setGoalPos(posStatic[3]);
            // serv5.setGoalPos(posStatic[4]);
        }
    }
}