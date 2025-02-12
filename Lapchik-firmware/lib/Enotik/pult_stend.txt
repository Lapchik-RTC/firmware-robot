#include "crc8.h"
#include "Enotik.h"
#include "enotik_master.h"
#include "Enotik_message_format.h"
#include "parser.h"
#include "Periph.h"
#include "ryabina.h"
#include <Servo.h>

void setup() {
  Serial1.begin(19200);
  Serial.begin(9600);
  Enotik.init_master(0x01);
  // pinMode(axis_X, INPUT);
  // pinMode(axis_Y, INPUT);
}



void loop() 
{
  //Enotik.work();
  //  Serial.println(analogRead(A9));
  byte x = map(analogRead(A9), 0, 1023, 0, 255);
  byte y = map(analogRead(A7), 0, 1023, 0, 255);
  // byte x = map(analogRead(A8), 0, 1023, 0, 255);
  // byte y = map(analogRead(A11), 0, 1023, 0, 255);
  byte a = digitalRead(4);
  byte b = digitalRead(3);
  Serial.print(x);
  Serial.print("\t");
  Serial.println(y);
  Enotik.send_message(2, a, 1);
  Enotik.send_message(3, b, 1);
  Enotik.send_message(4, x, y);
}
