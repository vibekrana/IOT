#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <RTClib.h>  // Use RTClib library instead of DS1307RTC

#define DHT_PIN 2          // Pin for DHT sensor
#define LDR_PIN A0         // Pin for Light Sensor (LDR)
#define BUZZER_PIN 3       // Pin for buzzer
#define ALARM_HOUR 7       // Set alarm hour (24-hour format)
#define ALARM_MINUTE 30    // Set alarm minute

#define DHT_TYPE DHT11     // Define DHT sensor type (DHT11 or DHT22)
DHT dht(DHT_PIN, DHT_TYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD object
RTC_DS1307 rtc;  // Initialize RTC object

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  lcd.begin(16, 2);              // Initialize LCD
  lcd.print("Smart Alarm Clock");
  delay(2000);
  lcd.clear();

  dht.begin();                  // Initialize DHT sensor
  if (!rtc.begin()) {           // Initialize DS1307 RTC
    lcd.print("RTC Error");
    while (1);
  }

  if (!rtc.isrunning()) {       // Check if RTC is running
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC time to compile time
  }

  delay(1000);                  // Short delay before starting
}

void loop() {
  // Read current time from DS1307 RTC
  DateTime now = rtc.now();

  // Read temperature and light level
  float temperature = dht.readTemperature();
  int lightLevel = analogRead(LDR_PIN);

  // Display the current time and temperature on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  
  // Check if it's time for the alarm
  if (now.hour() == ALARM_HOUR && now.minute() == ALARM_MINUTE) {
    if (lightLevel < 500) {  // Low light level (e.g., in the morning or night)
      // Activate alarm buzzer
      soundAlarm();
    }
  }

  // Optionally, check for temperature-based alarm adjustments (e.g., warmer mornings)
  if (temperature > 30) {
    // If the temperature is very high, adjust alarm behavior (e.g., turn off alarm if too hot)
    lcd.setCursor(0, 1);
    lcd.print("Too hot to sleep!");
    delay(2000); // Show for a while
  }

  delay(1000);  // Delay for a second before next loop iteration
}

void soundAlarm() {
  // Sound the buzzer for 5 seconds
  digitalWrite(BUZZER_PIN, HIGH);
  delay(5000);
  digitalWrite(BUZZER_PIN, LOW);
}
