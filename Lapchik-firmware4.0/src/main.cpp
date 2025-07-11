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

    // Serial.println(Serv[3].getRealSpd());
    for(int i = 0; i < 6; i++)
        Serv[i].setPos(0.0);
    
    for(int i = 0; i < 6; i++)
    {
        Serv[i].tick();
    }
}
