#include <Arduino.h>

bool perehodFix = 1;
float posStatic[6] = {0,0,0,0,0,0};



#include "encoder.h"
#include "obekti.h"
#include "phese.h"
void statPosUpd()
{
    posStatic[0] = enc_1.get_phi();
    posStatic[1] = enc_2.get_phi();
    posStatic[2] = enc_3.get_phi();
    posStatic[3] = enc_4.get_phi();
    posStatic[4] = enc_5.get_phi();
    posStatic[5] = enc_6.get_phi();
}
#include "orkestr.h"

Orkestr robot;
void setup() {
    Serial.begin(115200);
    
    float tc = 2.0*M_PI;
    float ts = 2.7;//4.6;//2.0*2.0/3.6*M_PI;
    float phiS = 0.5;
    float phi0 = 0;//M_PI;
    
    robot.setParams(M_PI, tc, ts, phiS, phi0);
    robot.calibr();
    robot.stendUp();
}


void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    

    static uint32_t t = millis();
    static bool a = 1, b = 1;

    float v = 3.0;
    if(a)
    {
        statPosUpd();
        a = 0;
    }
    int timeWork = 6000;
    while((millis() - t) < timeWork)
    {
        robot.turnL(v);
        // if(millis() - t == timeWork - 1)
        // {
        //     statPosUpd();
        // }
    }
    while (millis() - t < 11000)
    {
        serv1.setGoalSpeed(-0.3);
        serv2.setGoalSpeed(-0.3);
        serv3.setGoalSpeed(-0.3);
        serv4.setGoalSpeed(-0.3);
        serv5.setGoalSpeed(-0.3);
        serv6.setGoalSpeed(-0.3);
    }
    if(b)
    {
        robot.calibr();
        robot.stendUp();
        b = 0;
    }
    robot.Foo(v);
    // robot.ostanovka();
    
    
    // while (1);
    
}







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

    // Serial.print(enc_5.get_tick());
    // Serial.print("\tenc6: ");
    // Serial.print(enc_6.get_tick());
    // Serial.print('\n');

    // Serial.print("\tenc6_A: ");
    // Serial.print(digitalRead(12));
    // Serial.print("\tenc6_B: ");
    // Serial.print(digitalRead(14));
    // Serial.print('\n');

    // serv1.setGoalPos(M_PI/6);
    // serv2.setGoalPos(M_PI/6);
    // serv3.setGoalPos(M_PI/6);
    // serv4.setGoalPos(M_PI/6);
    // serv5.setGoalPos(M_PI);
    // serv6.setGoalPos(M_PI/6);
    /*for(int i = 0; i < 6; i++)
    {
        Serial.print("\tcs" + String(i) + ": " + analogRead(csPins[i]));
    }*/
    // Serial.print("\tcs" + String(1) + ": " + analogRead(csPins[0]));
    // Serial.print('\n');


    // Serial.print(enc_5.get_phi());
    // Serial.print(" ");
    // Serial.print(enc_5.get_w_moment_rad());
    // Serial.print(" ");
    // Serial.print('\n');






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