#include <LiquidCrystal.h>

#define POT_PIN A0           // Pin for potentiometer (soil moisture simulation)
#define RELAY_PIN 3          // Pin for controlling water pump (Relay)
#define BUTTON_PIN 4         // Pin for manual control button

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int soilMoistureValue = 0;   // Soil moisture (simulated by potentiometer)
int moistureThreshold = 500;  // Threshold for moisture (arbitrary)
bool watering = false;       // Flag for watering status
bool manualControl = false;  // Flag for manual control

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button for manual override

  lcd.begin(16, 2);
  lcd.print("Smart Irrigation");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read soil moisture level (simulated by potentiometer)
  soilMoistureValue = analogRead(POT_PIN);

  // Display readings on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(soilMoistureValue);

  // Check for manual override
  if (digitalRead(BUTTON_PIN) == LOW) {
    manualControl = !manualControl;
    delay(500);  // Debounce
  }

  // Check if it's time to water based on soil moisture
  if (manualControl) {
    lcd.setCursor(0, 1);
    lcd.print("Manual Control");
    digitalWrite(RELAY_PIN, HIGH);  // Turn on water pump
    watering = true;
  } else {
    if (soilMoistureValue < moistureThreshold) {  // Dry soil condition
      digitalWrite(RELAY_PIN, HIGH);  // Turn on water pump
      watering = true;
    } else {
      digitalWrite(RELAY_PIN, LOW);   // Turn off water pump
      watering = false;
    }
  }

  // Show watering status
  if (watering) {
    lcd.setCursor(0, 1);
    lcd.print("Watering On   ");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Watering Off  ");
  }

  delay(1000); // Delay for a second before next reading
}
