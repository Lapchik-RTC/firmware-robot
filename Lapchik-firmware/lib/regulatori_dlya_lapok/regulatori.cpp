#include"regulatori.h"

ServoMotor::ServoMotor(MotorParams *mp, MotorControlParams *mctrlp)
:MotorParams(*mp), MotorControlParams (*mctrlp)
{
    
}

void writePwm(float pwm);

float ServoMotor::PIreg(float err)
{
    static float P, I = 0;
    P = err * kp;
    I = I + err * ki * Ts_s;
    if (I > maxI) { I = maxI; }
    return P + I;
}

// float PIreg::tick(float err){
//     P = err * kp;
//     I = I + err * ki * Ts;
//     I = constrain(I, -maxI, maxI);
//     return P + I;
// }

// float Lapka::getRealSpeed(){
//     static int count = 0;
//     static int32_t enc = 0;
//     static int32_t encCounter = 0;
//     static int32_t timer = millis();
//     timer = millis();
//     while (millis() - timer < 10) {
//         noInterrupts();
//         count = enc;
//         enc = 0;
//         interrupts();
//         encCounter += count;
//   }
//   realSpeed = 200.0 * M_PI * (encCounter * 1.0 / 470);  //скорость в тиках за 10 милисекунд
//   encCounter = 0.0;
//   timer = millis();
//   return realSpeed;
// }