#include <Arduino.h>

bool perehodFix = 1;
float posStatic[6] = {0,0,0,0,0,0};


#include "encoder.h"
#include "obekti.h"
#include "phese.h"
#include "orkestr.h"
#include "svyaz.h"
#include "nastroeniya.h"

void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);

    memset(&gamePad, 0, sizeof(gamePad));

    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    
    robot.setParams(M_PI, tc, ts, phiS, phi0);
}


void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    
    readPacket();

    stateMachine();    
    Serial.print("\tgamePad.RightThumbY: " + String(gamePad.RightThumbY) + "\tgamePad.RightThumbX: " + String(gamePad.RightThumbX) + "\tgamePad.B: " + String(gamePad.B));
    Serial.println();
    /*
    static uint32_t t = millis();
    float v = 3.0;
    static bool a = 1;
    if(a)
    {
        statPosUpd();
        a = 0;
    }
    int timeWork = 6000;
    
    robot.ostCalibr();
    t = millis();
    while((millis() - t) < timeWork)
    {
        robot.turnL(v);
    }

    robot.ostCalibr();
    t = millis();

    while((millis() - t) < timeWork)
    {
        robot.turnR(v);
    }
    
    robot.ostCalibr();
    t = millis();

    while(millis() - t < timeWork)
    {
        robot.Foo(v);
    }*/
}