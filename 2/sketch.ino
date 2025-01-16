#include <LiquidCrystal.h>

#define LIGHT_PIN 2    
#define FAN_PIN 3      
#define LIGHT_BUTTON 4 
#define FAN_BUTTON 5   

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

bool lightStatus = false;
bool fanStatus = false;

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);    
  pinMode(FAN_PIN, OUTPUT);        
  pinMode(LIGHT_BUTTON, INPUT_PULLUP);  
  pinMode(FAN_BUTTON, INPUT_PULLUP);    

  lcd.begin(16, 2);
  lcd.print("Home Automation");
  delay(2000);
  lcd.clear();
  displayStatus();
}

void loop() {
  if (digitalRead(LIGHT_BUTTON) == LOW) { 
    lightStatus = !lightStatus; 
    digitalWrite(LIGHT_PIN, lightStatus ? HIGH : LOW);
    displayStatus();
    delay(500); // Debounce delay
  }

  if (digitalRead(FAN_BUTTON) == LOW) { 
    fanStatus = !fanStatus; 
    digitalWrite(FAN_PIN, fanStatus ? HIGH : LOW);
    displayStatus();
    delay(500); 
  }
}

void displayStatus() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(lightStatus ? "ON" : "OFF");
  lcd.setCursor(0, 1);
  lcd.print("Fan: ");
  lcd.print(fanStatus ? "ON" : "OFF");
}
