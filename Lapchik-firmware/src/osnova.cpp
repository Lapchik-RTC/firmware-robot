#include <Arduino.h>
bool calibr152 = 0;
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

void printPacket() {
    if (readPacket()) {
      Serial.println("Valid packet:");
      Serial.print("LeftThumbX: "); Serial.print(gamePad.LeftThumbX);
      Serial.print(" LeftThumbY: "); Serial.print(gamePad.LeftThumbY);
      if(gamePad.LeftThumbPress) Serial.println("  Левый стик нажат! ");
      else Serial.println("  Левый НЕ стик нажат! ");
  
      Serial.print("RightThumbX: "); Serial.print(gamePad.RightThumbX);
      Serial.print(" RightThumbY: "); Serial.print(gamePad.RightThumbY);
      if(gamePad.RightThumbPress) Serial.println("  Правый стик нажат! ");
      else Serial.println("  Правый НЕ стик нажат! ");
      Serial.print("Buttons: ");
      if(gamePad.A) Serial.print("A ");
      if(gamePad.B) Serial.print("B ");
      if(gamePad.X) Serial.print("X ");
      if(gamePad.Y) Serial.print("Y; ");
      if(gamePad.DPad_Up) Serial.print("DPad_Up ");
      if(gamePad.DPad_Down) Serial.print("DPad_Down ");
      if(gamePad.DPad_Left) Serial.print("DPad_Left ");
      if(gamePad.DPad_Right) Serial.println("DPad_Right ");
    } else if(gamePad.CRC_Error) {
      Serial.println("CRC Error!");
    }
  // delay(20);
  }
  

void loop(){
    // static uint64_t timer = micros();
    // while(micros() - timer < Ts_s);
    // timer = micros();
    // Serial.print(gamePad.B);

    // printPacket();
    // delay(500);
    readPacket();

    if (nado_rabotat()) {
        // readPacket();
        // Serial.println("21111111111");

        stateMachine();

    }
    else {
        statPosUpd();
        while (!nado_rabotat()){
            readPacket();
            // Serial.print("...");
                serv2.setGoalPos(posStatic[2 - 1]);
                serv3.setGoalPos(posStatic[3 - 1]);
                serv6.setGoalPos(posStatic[6 - 1]);  
                serv1.setGoalPos(posStatic[1 - 1]);
                serv4.setGoalPos(posStatic[4 - 1]);
                serv5.setGoalPos(posStatic[5 - 1]);
            
        }
    }
    // Serial.println();
    // Serial.print("\tgamePad.RightThumbY: " + String(gamePad.RightThumbY) + "\tgamePad.RightThumbX: " + String(gamePad.RightThumbX) + "\tgamePad.B: " + String(gamePad.B));
    // Serial.println();
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