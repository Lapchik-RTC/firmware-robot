#include <Arduino.h>

#include "encoder.h"
#include "orkestr.h"
#include "obekti.h"

// Orkestr robot;

void setup() {   
    Serial.begin(115200);
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();

    // encUpd();

    float tc = 7.7;//2.0*M_PI;
    float ts = 5.0;//2.0*2.0/3.6*M_PI;
    float phiS = 2.5;//1.5;
    float phi0 = 2.0;

    
    // robot.Foo(((enc_4.get_w_moment_rad()+1.5)*Ts_s), tc, ts, phiS, phi0);

    // enc_5.enc_tick();
    // dvigatel_5.update_voltage_in_V(1);
    // serv5.setGoalSpeed(1);
    serv5.setGoalPos(10);

    Serial.print(enc_5.get_phi());
    Serial.print(" ");
    Serial.print(enc_5.get_w_moment_rad());
    Serial.print(" ");
    Serial.print('\n');

}






//////////////////////////////////////////////////////////

    // dvigatel_4.update_voltage_in_V(
    //     serv4.setGoalSpeed( serv4.setGoalPos(enc_5.get_phi(), enc_4.get_phi()), enc_5.get_w_moment_rad())
    // );

    //t.tripod();
    
    // Serial.print('\t');
    // Serial.println();

    //enc_4.enc_tick();
    // dvigatel_4.update_voltage_in_V(
    //     serv4.setGoalSpeed(enc_5.get_w_moment_rad()*1.0, enc_4.get_w_moment_rad()*1.0)
    // );
    
    // Serial.print('\t');
    // Serial.println(enc_5.get_phi());


/*
ISR(PCINT0_vect)
{
    value++;
}

ISR(PCINT2_vect)
{
    value--;
}*/

    /*enc_1.enc_tick();
    enc_2.enc_tick();
    enc_3.enc_tick();
    enc_4.enc_tick();
    enc_5.enc_tick();
    enc_6.enc_tick();
    // Serial.println(enc_6.get_tick());
    // Serial.println(enc_6.get_tick());
    Serial.print(enc_1.get_tick());
    Serial.print("\t");
    Serial.print(enc_2.get_phi());
    Serial.print("\t");
    Serial.print(enc_3.get_phi());
    Serial.print("\t");
    Serial.print(enc_4.get_phi());
    Serial.print("\t");
    Serial.print(enc_5.get_phi());
    Serial.print("\t");
    Serial.println(enc_6.get_phi());*/