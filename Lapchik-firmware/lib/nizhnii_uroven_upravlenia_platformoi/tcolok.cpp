#include <Arduino.h>
#include "tcokol.h"

void motore(int vel)
{
  digitalWrite(3, vel >= 0);
  digitalWrite(4, !(vel > 0));

  vel = abs(vel);
  if (vel > 255) vel = 255;
  analogWrite(10, vel);


}