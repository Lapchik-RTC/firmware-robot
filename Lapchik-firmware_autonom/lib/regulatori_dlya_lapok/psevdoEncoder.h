#ifndef ENCODER
#define ENCODER
#include<Arduino.h>
#define I_PIN1 62
#define D_PIN1 63
#define ENC_DIR1 1
#define I_PIN2 64
#define D_PIN2 65
#define ENC_DIR2 1
#define I_PIN3 66
#define D_PIN3 67
#define ENC_DIR3 1
#define I_PIN4 69
#define D_PIN4 68
#define ENC_DIR4 1
#define I_PIN5 10
#define D_PIN5 11
#define ENC_DIR5 1
#define I_PIN6 12
#define D_PIN6 13
#define ENC_DIR6 1
volatile int32_t enc1 = 0, enc2 = 0, enc3 = 0, enc4 = 0, enc5 = 0, enc6 = 0;
void EncTick1();
void EncTick2();
void EncTick3();
void EncTick4();
void EncTick5();
void EncTick6();
void encInit(){
    attachInterrupt(digitalPinToInterrupt(I_PIN1), EncTick1, 3);
    attachInterrupt(digitalPinToInterrupt(I_PIN2), EncTick2, 3);
    attachInterrupt(digitalPinToInterrupt(I_PIN3), EncTick3, 3);
    attachInterrupt(digitalPinToInterrupt(I_PIN4), EncTick4, 3);
    attachInterrupt(digitalPinToInterrupt(I_PIN5), EncTick5, 3);
    attachInterrupt(digitalPinToInterrupt(I_PIN6), EncTick6, 3);
}

/////////   ENCODER1   /////////
void EncTick1()
{
    if(digitalRead(D_PIN1))
    {
        enc1+=ENC_DIR1;
    }
    else
    {
        enc1-=ENC_DIR1;
    }
}

/////////   ENCODER2   /////////
void EncTick2()
{
    if(digitalRead(D_PIN2))
    {
        enc2+=ENC_DIR2;
    }
    else
    {
        enc2-=ENC_DIR2;
    }
}

/////////   ENCODER3   /////////
void EncTick3()
{
    if(digitalRead(D_PIN3))
    {
        enc3+=ENC_DIR3;
    }
    else
    {
        enc3-=ENC_DIR3;
    }
}

/////////   ENCODER4   /////////
void EncTick4()
{
    if(digitalRead(D_PIN4))
    {
        enc4+=ENC_DIR4;
    }
    else
    {
        enc4-=ENC_DIR4;
    }
}

/////////   ENCODER5   /////////
void EncTick5()
{
    if(digitalRead(D_PIN5))
    {
        enc5+=ENC_DIR5;
    }
    else
    {
        enc5-=ENC_DIR5;
    }
}

/////////   ENCODER6   /////////
void EncTick6()
{
    if(digitalRead(D_PIN6))
    {
        enc6+=ENC_DIR6;
    }
    else
    {
        enc6-=ENC_DIR6;
    }
}
#endif