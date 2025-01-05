#include <LiquidCrystal_PCF8574.h>
#include <SoftwareSerial.h>


//Bluetooth-Pins
#define BTRX D2
#define BTTX D3
//Motor-Pins
#define M1PINPWM D9
#define M1DIR D7
#define M2PINPWM D10
#define M2DIR D8

LiquidCrystal_PCF8574 lcd(0x27);
SoftwareSerial SerialBT(BTRX, BTTX);

String data;
char cMessage;
int iMessage;
bool isInt, isForwarding, isBackwarding, isTurningLeft, isTurningRight, handbrake;

int PWM, pwm_ratio, LPG_x;

void setup() {
  I2C_LCD_Init();
  Serial.begin(115200);
  SerialBT.begin(9600);
  pinMode(M1PINPWM, OUTPUT);
  pinMode(M1DIR, OUTPUT);
  pinMode(M2PINPWM, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  analogWriteFrequency(20000);
  analogWriteResolution(8);
}

void loop() {
  if(SerialBT.available()) {
    data = SerialBT.readStringUntil('\n');
    if(data.startsWith("c")) {
      cMessage = data[1];
      isInt = false;
    } else if(data.startsWith("i")) {
      iMessage = data.substring(1).toInt();
      isInt = true;
    }

    if(isInt) {
      PWM = iMessage;
      if(!handbrake) {
        if(isForwarding) {
          forward();
        }
        if(isBackwarding) {
          backward();
        }
      }
    } else {
      if(cMessage == '0') {
        if(!handbrake) {
        forward();
        }
        isForwarding = true;
        isBackwarding = false;
        isTurningLeft = false;
        isTurningRight = false;
        Serial.println("cGangHoch");
      }
      if(cMessage == '1') {
        if(!handbrake) {
          backward();
        }
        isForwarding = false;
        isBackwarding = true;
        isTurningLeft = false;
        isTurningRight = false;
        Serial.println("cGangRunter");
      }
      if(cMessage == '2') {
        if(!handbrake) {
          turnLeft();
        }
        isForwarding = false;
        isBackwarding = false;
        isTurningLeft = true;
        isTurningRight = false;
        Serial.println("cLinks");
      }
      if(cMessage == '3') {
        if(!handbrake) {
          turnRight();
        }
        isForwarding = false;
        isBackwarding = false;
        isTurningLeft = false;
        isTurningRight = true;
        Serial.println("cRechts");
      }
      if(cMessage == '4') {
        handbrake = false;
        Serial.println("Handbremse los");
      }
      if(cMessage == '5') {
        handbrake = true;
        brake();
        Serial.println("Handbremse");
      }
    }
  }
  I2C_LCD_draw();
}