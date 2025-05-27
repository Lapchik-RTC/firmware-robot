#include <Arduino.h>

#include "stateMachine.h"
#include "hall.h"

StateMachine sm;
Hall halls;
void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);

    memset(&gamePad, 0, sizeof(gamePad));

    // halls.Init();
    sm.preState();
    sm.setSpd( 3.5 );

}

void loop(){
    readPacket();
    // halls.Upd();
    sm.StateMachineUpd();
}
