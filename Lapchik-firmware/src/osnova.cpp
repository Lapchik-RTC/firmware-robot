#include <Arduino.h>


//#include "regulatori.h"
#include "encoder.h"
#include "orkestr.h"



#include "obekti.h"
//volatile int value = 0;



void setup() {
    
    Serial.begin(9600);
}

//#define Ts_us 5000 // Период квантования в [мкс]
//#define Ts_s (Ts_us / 1000000.0) // Период квантования в [с]
//обьявленно выше


void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();

    
    
    enc_1.enc_tick();
    enc_2.enc_tick();
    enc_3.enc_tick();
    enc_4.enc_tick();
    enc_5.enc_tick();
    enc_6.enc_tick();

    Orkestr tri;
    float tc = 2*M_PI;
    float ts = 2*2/3.6*M_PI;
    float phiS = 1.5;
    float phi0 = -2.0;
    tri.Foo(((enc_4.get_w_moment_rad()+2.0)*Ts_s), tc, ts, phiS, phi0);
    // t.tripod();
     Serial.print('\n');

    // dvigatel_4.update_speed_in_rad(
    //     serv4.setGoalSpeed( serv4.setPoint(enc_5.get_phi(), enc_4.get_phi()), enc_5.get_w_moment_rad())
    // );

    //t.tripod();
    
    // Serial.print('\t');
    // Serial.println();

    //enc_4.enc_tick();
    // dvigatel_4.update_speed_in_rad(
    //     serv4.setGoalSpeed(enc_5.get_w_moment_rad()*1.0, enc_4.get_w_moment_rad()*1.0)
    // );
    
    // Serial.print('\t');
    // Serial.println(enc_5.get_phi());
}


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