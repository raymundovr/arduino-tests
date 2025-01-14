#include <LiquidCrystal.h>
#define TEMP_PIN 0

// init pins for interface
// RS, E, DB4, ..., DB7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const int WIDTH = 16, COLS = 2;
void setup() {
  // columns and rows
  lcd.begin(WIDTH, COLS);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Temp         C");
  lcd.setCursor(6, 0);
  lcd.print(getTemperatureCelsius());

  // second method
  lcd.setCursor(0, 1);
  lcd.print("Temp         C");
  lcd.setCursor(6, 1);
  lcd.print(getTempCelsius());
  delay(5000);
}

float getTemperatureCelsius() {
  int tempReading = analogRead(TEMP_PIN);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  return tempK - 273.15;            // Convert Kelvin to Celcius
}

// This was indicated as the original method in the commented code from samples
float getTempCelsius() {
  int tempReading = analogRead(TEMP_PIN);
  float tempVolts = tempReading * 5.0 / 1024.0;
  return (tempVolts - 0.5) * 10.0;
}

void printMessage() {
  lcd.print("Ninia...");
  String msg = "Comete tus calzones nuevos  ";
  // col, row

  for(int i =0; i < msg.length() - WIDTH; i++) {
    lcd.setCursor(0, 1);
    lcd.print(msg.substring(i, i + WIDTH));
    delay(1000);
  }
}