<<<<<<< HEAD


#include "regulatori.h"

PIreg::PIreg(float kp, float ki, float maxI, float Ts){
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
=======
>>>>>>> 349cd65d4364c43e95193210b24d0ef92a208e7f
