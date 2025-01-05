#define LED D13
#define pot A0

int PWM;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(pot, INPUT);
  analogWriteFrequency(4000);
  analogWriteResolution(10);
}

void loop() {
  PWM = analogRead(pot);
  analogWrite(LED, PWM);
}