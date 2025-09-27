#include <Arduino.h>
#include "SLOVAR.h"
#include "obekti.h"
#include "stateMachine.h"
// #include "hall.h"
#include "softCheck.h"

void setup() {
  Serial.begin(115200);
  Serial1.begin(19200);

  memset(&gamePad, 0, sizeof(gamePad));
  pinMode(BUTTON_PIN, 2);
  // sm.preState();
  float tc = 2.0 * M_PI;
  float ts = 2.7;  
  float phiS = 0.5;
  float phi0 = 0;
  // robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
  robot.setParams(0 /*M_PI*/, tc, 2.4, 0.25, phi0);
  robot.calibr();
  // robot.stendUp2();
  robot.allEncZero();
}


////////////
enum States {
  WAIT_BUTTON,
  SQUARE_WALK,
  FORW_WALK
};
////////////

// States buttonUpd(uint32_t t = 30)
// {
//   static uint32_t timer = milis();
//   static uint8_t int click = 0;
//   if(digitalRead(BUTTON_PIN))
//   {
//     timer = milis();
//     click++;
//   }
// }

void loop() {
  static uint64_t timer = micros();
  while (micros() - timer < Ts_s)
    ;
  timer = micros();
  // static States state = WAIT_BUTTON;
  // state = buttonUpd();




  readPacket();
  sm.StateMachineUpd();

  // int tTurn = 3000;
  // int tForw = 5500;
  // int mDelay = 1800;
  // float vForw = 3.0;

  // static int32_t stt = millis();
  // if (millis() - stt < mDelay) {
  //   robot.Foo(0.0, 0.0, 0.0);
  // } else if (millis() - stt < mDelay + tForw) {
  //   robot.Foo(vForw, 0.0, 0.0);
  // } else if (millis() - stt < 2 * mDelay + tForw) {
  //   robot.Foo(0.0, 0.0, 0.0);
  // } else if (millis() - stt < 2 * mDelay + tForw + tTurn) {
  //   robot.turnL(vForw);
  // } else if (millis() - stt < 3 * mDelay + tForw + tTurn) {
  //   robot.Foo(0.0, 0.0, 0.0);
  // } else {

  //   // robot.setParams(0, 2.0*M_PI, 2.4, 0.25, 0);
  //   stt = millis();
  // }

  // robot.Foo(3.0, 0.0, 0.0);
  //*/
  // Serial.println("--------------");
  serv[0].tick();
  serv[1].tick();
  serv[2].tick();
  serv[3].tick();
  serv[4].tick();
  serv[5].tick();
}