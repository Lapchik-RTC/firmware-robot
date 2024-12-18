#define INA 11
#define INB 10
#define PWM 6

#define ENCA 2  // PD0
#define ENCB 4  // PA1
#define ENC_PPR 448
#define ENC_DIR -1
#define MDIR 1

#define KP 1.5
#define KI 50
#define KE 0.8
#define Ts_s 4000
volatile int32_t enc = 0;

void encoder();

void setup() {
  attachInterrupt(digitalPinToInterrupt(ENCA), encoder, 3);
  Serial.begin(9600);
  motorInit();
}

void getRealSpeed() {
}


void loop() {
  static float realSpeed = 0.0;
  static int32_t encCounter = 0;
  static int count = 0;
  static int32_t timer = millis();

  while (millis() - timer < 10) {
    //Serial.print(" ");
    noInterrupts();
    count = enc;
    enc = 0;
    interrupts();
    encCounter += count;
  }
  //realSpeed = ;
  realSpeed = 200.0 * M_PI * (encCounter * 1.0 / ENC_PPR); //скорость в радианах в секунду
  Serial.print(realSpeed);
  Serial.print('\t');
  Serial.print(encCounter);
  Serial.print('\t');
  Serial.println((millis() - timer));
  motor(20);
  encCounter = 0;
  //delay(100);
  timer = millis();
/////////////////////////////////////////////////////////////////////

}
