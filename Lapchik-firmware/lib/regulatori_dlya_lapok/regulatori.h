#pragma once
#include<Arduino.h>
//#include<SLOVAR>
#include"motor.h"
#include"encoder.h"

//#pragma once
// struct MotorConRegParams//структура для каждого
// {
//   byte csPin;
//   int csKalibr;
//   int *enc;
//   int ppr;
// };

struct MotorControlParams//структура общая
{
  float Ts;
  float kpPI;
  float ki;
  float maxI;
  float kpP;
  float kalibrSpeed;
};

///////////////////////   ServoPrivod   ///////////////////////
class ServoPrivod: public MotorControlParams, public Dvigatel, public Encoder
{
  private:
  float realSpeed, realAngle;
  Dvigatel &motor;
  Encoder &enc;
  int16_t ImasNum;
  float PIreg(float err);
  //inline float Preg(float err);

  public:
  ServoPrivod(MotorControlParams *mconp, Dvigatel &motor, Encoder &enc, int16_t ImasNum) 
  : MotorControlParams(*mconp), Dvigatel(motor), Encoder(enc) {
    this->ImasNum = ImasNum;
  }
  void setGoalSpeed(float goalSpeed);//rad/s
};

///////////////// REGULATORI /////////////////
float ServoPrivod::PIreg(float err)
{
    float P;
    P = err * kpPI;
    // Imas[this->ImasNum] += err * ki * Ts;
    // if (Imas[this->ImasNum] > maxI) { Imas[this->ImasNum] = maxI; }
    
    return P ;//+ Imas[this->ImasNum];
    
    
    /*Serial.print('\t');
    Serial.print("I: ");
    Serial.print(Imas[this->ImasNum]);
    Serial.print('\t');//*/
}



/*void ServoPrivod::setAngle(float goalAng)
{
  //realSpeed = getRealSpeed();
  //if(enc->get_tick() % ppr == 0){enc = 0;}
  //realAngle = (enc->get_tick() / ppr) * 2 * M_PI;
  float u = Preg(goalAng - enc.get_phi());
  setGoalSpeed(u);  
}*/

///////////////// GET /////////////////
// float ServoPrivod::getRealSpeed()
// {
//   static int count = 0;
//   static int32_t encCounter = 0;
//   static int32_t timer = millis();
  
//   timer = millis();
//   while (millis() - timer < 10) {
//     noInterrupts();
//     count = enc.get_tick();
//     enc.get_tick = 0;
//     interrupts();
//     encCounter += count;
//   }
//   realSpeed = 200.0 * M_PI * (encCounter * 1.0 / ppr);/*ENC_PPR450*/  //скорость в радиранах за 10 милисекунд
//  // enc += encCounter;
//   encCounter = 0.0;
//   timer = millis();
//   return realSpeed;
// }