#include <Arduino.h>

#include "encoder.h"
#include "orkestr.h"
#include "obekti.h"

//#define sgn(a) (a > 0? 1 : a < 0? -1 : 0)

Orkestr robot;

void setup() {   
    Serial.begin(115200);

    // float tc = 8;//2.0*M_PI;
    // float ts = 4.6;//2.0*2.0/3.6*M_PI;
    // float phiS = 1.5;
    // float phi0 = -M_PI;

    robot.setParams(0, tc, ts, phiS, phi0);

}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();

    //encUpd();
    // enc_1.enc_tick();
    // enc_2.enc_tick();
    // enc_3.enc_tick();
    // enc_4.enc_tick();
    enc_5.enc_tick();
     enc_6.enc_tick();
    
    //robot.Foo(2);
    
    //dvigatel_3.update_voltage_in_V(5);

    // dvigatel_5.update_voltage_in_V(1);a
    
    // Serial.print("\tenc1: ");
    // Serial.print(enc_1.get_tick());
    // Serial.print("\tenc2: ");
    // Serial.print(enc_2.get_tick());
    // Serial.print("\tenc3: ");
    // Serial.print(enc_3.get_tick());
    // Serial.print("\tenc4: ");
    // Serial.print(enc_4.get_tick());
    // Serial.print("\tenc5: ");

    Serial.print(enc_5.get_tick());
    Serial.print("\tenc6: ");
    Serial.print(enc_6.get_tick());
    Serial.print('\n');

    // Serial.print("\tenc6_A: ");
    // Serial.print(digitalRead(12));
    // Serial.print("\tenc6_B: ");
    // Serial.print(digitalRead(14));
    // Serial.print('\n');

    // for(int i = 0; i < 6; i++)
    // {
    //     Serial.print("cs" + String(i) + ": " + analogRead(csPins[i]) + '\t');
    // }


    // Serial.print(enc_5.get_phi());
    // Serial.print(" ");
    // Serial.print(enc_5.get_w_moment_rad());
    // Serial.print(" ");
    // Serial.print('\n');

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