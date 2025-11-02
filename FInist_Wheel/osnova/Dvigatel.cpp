#include "Dvigatel.h"

Dvigatel::Dvigatel(DvigatelParams dvigatelParams) 
{
    this->dvigatelParams = dvigatelParams;

    pinMode(this->dvigatelParams.motor_in_1, OUTPUT);
    pinMode(this->dvigatelParams.motor_in_2, OUTPUT);
    pinMode(this->dvigatelParams.motor_pwm,  OUTPUT);
}

void Dvigatel::update_voltage_in_V(float u) 
{
    int16_t pwm = 255.0 * (u / dvigatelParams.supply_voltage) * 1.0/*dvigatelParams.motor_dir*/;
    pwm = constrain(pwm, -255.0, 255.0);

    if (pwm >= 0)
    {
      digitalWrite(this->dvigatelParams.motor_in_1, HIGH);
      digitalWrite(this->dvigatelParams.motor_in_2, LOW);
      analogWrite(this->dvigatelParams.motor_pwm, pwm);
    }
    else
    {
      digitalWrite(this->dvigatelParams.motor_in_1, LOW);
      digitalWrite(this->dvigatelParams.motor_in_2, HIGH);
      analogWrite(this->dvigatelParams.motor_pwm, abs(pwm));   // тут подавалось (255 + pwm)
    }
}