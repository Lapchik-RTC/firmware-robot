#include <Arduino.h>
#include "Parameters.h"
#include "Obj.h"
//#include "softCheck.h"

void setup() {
    Serial.begin(115200);

}


void loop() {
    static uint64_t timer = micros();
    while(micros() - timer < Ts_us);
    timer = micros();
    Serv[3].setSpeed(3.0);
    Serv[3].tick();
}
