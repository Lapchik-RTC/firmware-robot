#pragma once
#include<Arduino.h>
#include"Dvigatel.h"
#include"Encoder.h"
#include "f.h"
#include "Tau.h"

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

/////////////////////////////////////////////////////////////
//
///////////////////// SERVO_PRIVOD //////////////////////////
//
/////////////////////////////////////////////////////////////
class ServoPrivod
{
private:
  float realSpeed, realAngle;
  MotorControlParams params;
  Dvigatel *motor;
  Encoder *enc;
  float I;
  float PIreg(float err);
  float Preg(float err);
  
  enum CONTROL_MODE
  {
    MODE_POS,
    MODE_SPEED
  };
  CONTROL_MODE controlMode = MODE_SPEED;

  float targetSpeed = 0.0;
  float targetAngle = 0.0;

public:
  ServoPrivod(MotorControlParams mconp, Dvigatel *motor, Encoder *enc) {
    this->params = mconp;
    this->motor = motor;
    this->enc = enc;
  }
  void setGoalPos(float goalAngle);
  void setGoalSpeed(float goalSpeed);//rad/s

  void tick();
  
};

///////////////////////////////////////////////////////////
//
/////////////////////// SETS /////////////////////////////
//
///////////////////////////////////////////////////////////

void ServoPrivod::setGoalSpeed(float goalSpd)
{
  controlMode = MODE_SPEED;
  targetSpeed = goalSpd;
  // enc->enc_tick();
  // float realSpd = enc->get_w_moment_rad();

  // float u = PIreg(goalSpd - realSpd);

  // motor->update_voltage_in_V(u);
}

void ServoPrivod::setGoalPos(float goalAngle){
  controlMode = MODE_POS;
  targetAngle = goalAngle;
  // float phi = enc->get_phi();
  // float phi_err = phi0 - phi;
  // phi_err = fmod(phi_err, 2*M_PI);
  // //if(perehodFix){
  //   phi_err = modc(phi_err, 2*M_PI);
  // //}
  // float w0 = Preg(phi_err);
  
  // setGoalSpeed(w0);
}

void ServoPrivod::tick()
{
  enc->enc_tick();
  if(controlMode == MODE_POS)
  {
    float phi0 = enc->get_phi();
    float phi_err = targetAngle - phi0;
    
    phi_err = fmod(phi_err, 2*M_PI);
    phi_err = modc(phi_err, 2*M_PI);
    targetSpeed = Preg(phi_err);
    // Serial.println( String(phi0) );
  }
  motor->update_voltage_in_V( PIreg(targetSpeed - enc->get_w_moment_rad()) );
}


///////////////////////////////////////////////////////////
//
///////////////////// REGULATORI //////////////////////////
//
///////////////////////////////////////////////////////////
float ServoPrivod::PIreg(float err)
{
    float P = err * params.kpPI;
     
    float u = P + I;

    if (u == constrain(u, -params.maxU, params.maxU) || (err * u) < 0)
        I += err * params.Ts_sec * params.ki;

    return constrain(u, -params.maxU, params.maxU);
}

float ServoPrivod::Preg(float err){
  return constrain(err * params.kpP, -params.maxVel, params.maxVel);
}