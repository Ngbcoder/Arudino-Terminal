#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    
    // Check for Backlight Commands
    if (data == "BL_OFF") {
      lcd.noBacklight();
      lcd.clear();
    } else if (data == "BL_ON") {
      lcd.backlight();
    } else {
      // Normal display mode: Expects "Line1|Line2"
      int separatorIndex = data.indexOf('|');
      if (separatorIndex != -1) {
        String line1 = data.substring(0, separatorIndex);
        String line2 = data.substring(separatorIndex + 1);
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
      }
    }
  }
}
