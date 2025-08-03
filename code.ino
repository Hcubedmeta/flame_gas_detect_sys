#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Cảm biến
const int flameSensorPin = 2; // D2 - Cảm biến lửa dạng digital
const int gasSensorPin = A7;  // A7 - Cảm biến gas dạng analog
const int buzzel = 3;         // D3 - Còi báo động
const int relay = 4;          // D4 - Relay

// Ngưỡng phát hiện khí gas
const int gasThreshold = 400;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(flameSensorPin, INPUT);
  pinMode(buzzel, OUTPUT);
  pinMode(relay, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Khoi dong...");
  digitalWrite(buzzel, LOW);
  digitalWrite(relay, LOW);
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.clear();
  bool flameDetected = (digitalRead(flameSensorPin) == LOW);
  int gasValue = analogRead(gasSensorPin);
  bool gasDetected = (gasValue > gasThreshold);

  Serial.print("Gas: ");
  Serial.println(gasValue);

  if (flameDetected && gasDetected) {
    lcd.setCursor(0, 0);
    lcd.print("Lua & Gas ");
    lcd.setCursor(0, 1);
    lcd.print("Canh bao!");
    digitalWrite(buzzel, HIGH);
    digitalWrite(relay, HIGH);  // Có thể bật relay nếu dùng để thông gió, bơm hút gas...
  }
  else if (flameDetected) {
    lcd.setCursor(0, 0);
    lcd.print("phat hien lua");
    lcd.setCursor(0, 1);
    lcd.print("Canh bao lua!");
    digitalWrite(buzzel, HIGH);
    digitalWrite(relay, LOW);   // Không bật relay nếu chỉ có lửa
  }
  else if (gasDetected) {
    lcd.setCursor(0, 0);
    lcd.print("phat hien gas");
    lcd.setCursor(0, 1);
    lcd.print("bat quat");
    digitalWrite(buzzel, LOW);
    digitalWrite(relay, HIGH);  // Bật relay nếu chỉ có khí gas
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Ko co lua");
    lcd.setCursor(0, 1);
    lcd.print("Ko ro ri khi gas");
    digitalWrite(buzzel, LOW);
    digitalWrite(relay, LOW);
  }

  delay(500);
}
