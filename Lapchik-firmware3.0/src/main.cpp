#include <Arduino.h>
#include "SLOVAR.h"
#include "f.h"
#include "motorDriver.h"
#include "Isr_hendlers.h"
#include "encDriver.h"
#include "States.h"



motorParams MParams[6] = {
    {33, 35, 5, 1, SUPPLY_VOLTAGE},
    {32, 34, 4, 1, SUPPLY_VOLTAGE},
    {38, 36, 6, 1, SUPPLY_VOLTAGE},
    {37, 39, 7, 1, SUPPLY_VOLTAGE},
    {40, 42, 8, 1, SUPPLY_VOLTAGE},
    {41, 43, 9, 1, SUPPLY_VOLTAGE}
};

EncoderParams EParams[6] = {
    {64, 65, -1, ( 2.0*M_PI / kolvTickRate[0] ), 1746, get_AB_enc1, hallPin[0], kolvTickRate[0]*0.5},
    {62, 63, -1, ( 2.0*M_PI / kolvTickRate[1] ), 1824, get_AB_enc2, hallPin[1], kolvTickRate[1]*0.5},
    {66, 67, 1,  ( 2.0*M_PI / kolvTickRate[2] ), 1746, get_AB_enc3, hallPin[2], 0.0},
    {68, 69, 1,  ( 2.0*M_PI / kolvTickRate[3] ), 1746, get_AB_enc4, hallPin[3], 0.0},
    {10, 11, 1,  ( 2.0*M_PI / kolvTickRate[4] ), 1746, get_AB_enc5, hallPin[4], 0.0},
    {14, 15, 1,  ( 2.0*M_PI / kolvTickRate[5] ), 1746, get_AB_enc6, hallPin[5], 0.0}
};

Motor motors[6] = {
    {&MParams[0]},
    {&MParams[1]},
    {&MParams[2]},
    {&MParams[3]},
    {&MParams[4]},
    {&MParams[5]}
};

Encoder encs[6] = {
    {&EParams[0]},
    {&EParams[1]},
    {&EParams[2]},
    {&EParams[3]},
    {&EParams[4]},
    {&EParams[5]}
};

Dvigatel Dvigs[6] = {
    {&motors[1], &encs[1]},
    {&motors[0], &encs[0]},
    {&motors[2], &encs[2]},
    {&motors[3], &encs[3]},
    {&motors[4], &encs[4]},
    {&motors[5], &encs[5]}
};
Dvigatel *dvig_ptrs[6] = {&Dvigs[0], &Dvigs[1], &Dvigs[2], &Dvigs[3], &Dvigs[4], &Dvigs[5]};

State Foo(dvig_ptrs, _Foo);


void setup() {
  Serial.begin(115200);
  for(int i = 0; i < 6; i++)
  {
    encs[i].encZero();
  }
}

void loop() {
  static uint64_t timer = micros();
  while(micros() - timer < Ts_us);
  timer = micros();
  for(int i = 0; i < 6; i++)
  {
    encs[i].Tick();
  }
  Dvigs[0].setPos(0.0);
  // Foo.upd(3.0, 0.0);
}