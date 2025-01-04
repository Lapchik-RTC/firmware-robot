
#include"regulatori.h"
//////////////   Motor   //////////////
Motor::Motor(MotorParams *mp, MotorControlParams *mctrlp)
:MotorParams(*mp), MotorControlParams (*mctrlp)
{
    
}

//#include "regulatori.h"

PIreg::PIreg(float kp, float ki, float m1axI, float Ts){
    this->kp = kp;
    this->ki = ki;
    this->maxI = maxI;
    this->Ts = Ts;
}

float PIreg::tick(float err){
    P = err * kp;
    I = I + err * ki * Ts;
    I = constrain(I, -maxI, maxI);
    return P + I;
}

float Lapka::getRealSpeed(){
    static int count = 0;
    static int32_t enc = 0;
    static int32_t encCounter = 0;
    static int32_t timer = millis();
    timer = millis();
    while (millis() - timer < 10) {
        noInterrupts();
        count = enc;
        enc = 0;
        interrupts();
        encCounter += count;
  }
  realSpeed = 200.0 * M_PI * (encCounter * 1.0 / 470);  //скорость в тиках за 10 милисекунд
  encCounter = 0.0;
  timer = millis();
  return realSpeed;
}