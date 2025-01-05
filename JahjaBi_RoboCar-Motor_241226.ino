void forward() {
  M1CW();
  M2CCW();
}

void backward() {
  M1CCW();
  M2CW();
}

void brake() {
  M1brake();
  M2brake();
}

void turnRight() {
  M1CCW();
  M2CCW();
  delay(1000);
  brake();
}

void turnLeft() {
  M1CW();
  M2CW();
  delay(1000);
  brake();
}

void M1CW() {
  analogWrite(M1PINPWM, PWM);
  digitalWrite(M1DIR, HIGH);
}

void M1CCW() {
  analogWrite(M1PINPWM, PWM);
  digitalWrite(M1DIR, LOW);
}

void M1brake() {
  analogWrite(M1PINPWM, 0);
}

void M2CW() {
  analogWrite(M2PINPWM, PWM);
  digitalWrite(M2DIR, HIGH);
}

void M2CCW() {
  analogWrite(M2PINPWM, PWM);
  digitalWrite(M2DIR, LOW);
}

void M2brake() {
  analogWrite(M2PINPWM, 0);
}