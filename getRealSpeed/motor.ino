void motorInit() {
  pinMode(INA, 1);
  pinMode(INB, 1);
  pinMode(PWM, 1);
  pinMode(ENCA, 0);
  pinMode(ENCB, 0);
}
void motor(int mv) {
  digitalWrite(INA, mv < 0);
  digitalWrite(INB, mv > 0);
  analogWrite(PWM, min(abs(mv), 255));
}
void encoder() {
  // bool dir = digitalRead(ENCA) ^ digitalRead(ENCB);
  // enc += dir ? ENC_DIR : -ENC_DIR;
  if (digitalRead(ENCB)) {
    enc++;
  } else {
    enc--;
  }
}
