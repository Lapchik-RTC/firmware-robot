float PIreg(float err, float Ts) {
  static float P, I = 0;
  float maxI = 9999;
  P = err * KP;
  I = I + err * KI * Ts;
  if (I > maxI) { I = maxI; }
  return P + I;
}