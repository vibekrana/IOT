#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2       
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  lcd.begin(16, 2);  
  dht.begin();       
  lcd.print("Weather System");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(2000);  
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    lcd.clear();
    lcd.print("Sensor error");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humidity, 1);  
  lcd.print(" %");

  delay(5000);  
}
