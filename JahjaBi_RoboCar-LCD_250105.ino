//Initialisiert das LCD
void I2C_LCD_Init() {
  lcd.begin(16, 2);
  lcd.setBacklight(255);
}

//Zeichnet Inhalt des LCD
void I2C_LCD_draw() {
  lcd.clear();

  I2C_LCD_PWM();
  I2C_LCD_Brake();
  I2C_LCD_Instruction();
  I2C_LCD_VelocityBar();

  delay(100);
}

void I2C_LCD_PWM() {
  //Stellt die Geschwindigkeit (PWM) dar
  lcd.setCursor(1, 0);
  lcd.print(PWM);
}

void I2C_LCD_Brake() {
  //Stellt die Handbremse dar
  if(handbrake) {
    lcd.setCursor(5, 0);
    lcd.print("BRAKE");
  }
}

void I2C_LCD_Instruction() {
  //Stellt den letzten Befehl dar
  lcd.setCursor(11, 0);
  if(isForwarding) {
    lcd.print("GO");
  } else if(isBackwarding) {
    lcd.print("BACK");
  } else if(isTurningLeft) {
    lcd.print("LEFT");
  } else if(isTurningRight) {
    lcd.print("RIGHT");
  } else {
    lcd.print("-----");
  }
}

void I2C_LCD_VelocityBar() {
  //Füllt den Balken mit Platzhalterzeichen
  for(int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    if(i == 0) {
      lcd.write(91);
    } else if(i == 15) {
      lcd.write(93);
    } else {
      lcd.write(61);
    }
  }

  //Berechnet den PWM Wert pro Kästchen
  pwm_ratio = (int) (255 / 14);

  //Berechnet wieviele Kästchen gefüllt werden
  LPG_x = (int) (PWM / pwm_ratio);

  //Befüllt den Ladebalken in Abhängigkeit von den oberen Werten
  for(int j = 1; j <= LPG_x; j++) {
    lcd.setCursor(j, 1);
    lcd.write(255);
  }
}