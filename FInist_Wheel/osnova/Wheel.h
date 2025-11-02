//A6 - L
//A7 - R
//B - 26

#include "Arduino.h"
#pragma once

void wh_calibr() {
  uint32_t timer_wc = millis();
  while (((analogRead(CS_PIN_3) <= TRIG_CUR_3) || (analogRead(CS_PIN_4) <= TRIG_CUR_4)) && (millis() - timer_wc < 1000)) {
    serv[2].setGoalSpeed(1.2);
    serv[3].setGoalSpeed(1.2);
    serv[2].tick();
    serv[3].tick();
  }
  encod[2].encZero();
  encod[3].encZero();
  timer_wc = millis();
  while (millis() - timer_wc < 600) {
    serv[2].setGoalPos(-M_PI * 0.67);
    serv[3].setGoalPos(-M_PI * 0.67);
    serv[2].tick();
    serv[3].tick();
  }
  encod[2].encZero();
  encod[3].encZero();
}
