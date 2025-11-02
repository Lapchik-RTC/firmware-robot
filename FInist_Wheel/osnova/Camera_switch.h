#pragma once
void cam_init() {
  pinMode(27, 1);
  pinMode(29, 1);
  digitalWrite(27, 1);
  digitalWrite(29, 0);
}

void cam_switch() {
  static bool camState = 1;
  static uint32_t timerCam = millis();
  if (millis() - timerCam > 800) {
    if (camState) {
      camState = 0;
      digitalWrite(27, 0);
      digitalWrite(29, 1);
    } else {
      camState = 1;
      digitalWrite(27, 1);
      digitalWrite(29, 0);
    }
    timerCam = millis();
  }
}