#pragma once
#include<Arduino.h>
#include"Dvigatel.h"
#include"encoder.h"
#include "f.h"

struct MotorControlParams//структура общая
{
  float Ts_sec;
  float kpPI;
  float ki;
  float maxU; // Максимальное напряжение на двигателе
  float kpP;
  float maxVel; // Максимальная угловая скорость
  float kalibrSpeed;
};

///////////////////////   ServoPrivod   ///////////////////////
class ServoPrivod
{
private:
  MotorControlParams params;
  Dvigatel *motor;
  Encoder *enc;
  float I;
  float PIreg(float err);
  float Preg(float err);

  float targetSpeed = 0;
  float targetAngle = 0;

  enum CONTROL_MODE
  {
    MODE_POS,
    MODE_SPEED
  };

  CONTROL_MODE controlMode = MODE_SPEED;
  
public:
  ServoPrivod(MotorControlParams mconp, Dvigatel *motor, Encoder *enc)
  {
    this->params = mconp;
    this->motor = motor;
    this->enc = enc;
  }

  void tick();
  void setPos(float goalPosPhi);
  void setSpeed(float goalSpeed);
};

///////////////// REGULATORI /////////////////
float ServoPrivod::Preg(float err){
  return constrain(err * params.kpP, -params.maxVel, params.maxVel);
}

float ServoPrivod::PIreg(float err)
{
    float P = err * params.kpPI;
     
    float u = P + I;

    if (u == constrain(u, -params.maxU, params.maxU) || (err * u) < 0)
        I += err * params.Ts_sec * params.ki;

    return constrain(u, -params.maxU, params.maxU);
}


/////////////////   SETTING   /////////////////
void ServoPrivod::setSpeed(float goalSpd)
{
  controlMode = MODE_SPEED;
  targetSpeed = goalSpd;
}

void ServoPrivod::setPos(float phi0){
  controlMode = MODE_POS;
  targetAngle = phi0;
}


/////////////////    TICK    /////////////////
void ServoPrivod::tick()
{
  enc->enc_tick();

  if(controlMode == MODE_POS)
  {
    float phi = enc->get_mphi();
    float phi_err = targetAngle - phi; 
    // float phi_err = targetAngle - phi;
    phi_err = modc(phi_err, 2*M_PI);
    
    targetSpeed = Preg(phi_err);
  }
  
  float realSpd = enc->get_w_moment_rad();
  // Serial.print(realSpd);
  float u = PIreg(targetSpeed - realSpd);
  Serial.print(u);
  motor->update_voltage_in_V(u);
}