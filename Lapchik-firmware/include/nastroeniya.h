#pragma once
#include "svyaz.h"
Orkestr robot;
uint32_t pereriv = millis();
uint32_t pererivOst = millis();

void stateMachine()
{
    if(rovnaysa() && millis() - pererivOst > 10000)
    {
        pererivOst = millis();
        // delay(1000);
        calibr152 = 1;
        robot.ostCalibr();
        readPacket();
    }//*/
    if(vpered())
    {
        // while(vpered())
        // {
        Serial.println("vpered");
        // delay(1000);
        robot.Foo(4.5);
        // }
    }
    if(vpravo())
    {
        Serial.println("vpravo");
        // delay(1000);
        robot.turnR(4.5);
    }
    if(vlevo())
    {
        Serial.print("vlevo");
        // delay(1000);
        robot.turnL(4.5);
    }
    if(nazad())
    {
        Serial.print("nazad");
        // delay(1000);
        // robot.turnL(4.5);
        robot.ReversFoo(3.0, 3.0);
    }
/*else
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
    // Serial.print("dumau");
    while(!nado_rabotat())
    {
        Serial.println  ("dolgo dumau");
        serv2.setGoalPos(posStatic[1]);
        serv3.setGoalPos(posStatic[2]);
        serv6.setGoalPos(posStatic[5]);  
        serv1.setGoalPos(posStatic[0]);
        serv4.setGoalPos(posStatic[3]);
        serv5.setGoalPos(posStatic[4]);
    }*/
}//*/
