#include <Arduino.h>
#include "tcokol.h"

void motore() {
    int vel = 200;
    digitalWrite(2, !(vel >= 0));
    digitalWrite(3, (vel > 0));

    analogWrite(5, min(abs(vel), 255));
}