#include <LiquidCrystal.h>

#define AIR_SENSOR_PIN A0  // Analog pin for air quality simulation (Potentiometer)
#define BUZZER_PIN 3       // Pin for buzzer to indicate poor air quality

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer as output
  lcd.begin(16, 2);
  lcd.print("Air Quality Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  int airQuality = analogRead(AIR_SENSOR_PIN);  // Read air quality from potentiometer (simulating MQ-135)

  // Map the potentiometer value to a PPM range (0-1023 to 0-1000 for simplicity)
  int airQualityPPM = map(airQuality, 0, 1023, 0, 1000);

  // Display air quality
  lcd.setCursor(0, 0);
  lcd.print("Air Quality: ");
  lcd.print(airQualityPPM);
  lcd.print(" PPM");

  // Check air quality and trigger buzzer if necessary
  if (airQualityPPM > 500) { // Threshold value for poor air quality
    digitalWrite(BUZZER_PIN, HIGH); // Activate buzzer
    lcd.setCursor(0, 1);
    lcd.print("Poor Air Quality");
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Deactivate buzzer
    lcd.setCursor(0, 1);
    lcd.print("Air Quality OK");
  }

  delay(1000); // Update every second
}
