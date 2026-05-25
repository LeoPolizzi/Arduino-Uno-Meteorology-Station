#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN     2
#define DHTTYPE    DHT22
#define LED_RED    8
#define LED_GREEN  9

#define HOT  28.0
#define COLD 18.0

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastUpdate = 0;
const unsigned long UPDATE_MS = 2000;

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print(" Meteo Station ");
  lcd.setCursor(0, 1); lcd.print("  booting...   ");

  dht.begin();
  delay(1500);
  lcd.clear();
}

void loop() {
  if (millis() - lastUpdate < UPDATE_MS) return;
  lastUpdate = millis();

  float temp     = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp))     temp = 0;
  if (isnan(humidity)) humidity = 0;

  // Alert LEDs
  if (temp >= HOT)       { digitalWrite(LED_RED, HIGH); digitalWrite(LED_GREEN, LOW);  }
  else if (temp <= COLD) { digitalWrite(LED_RED, LOW);  digitalWrite(LED_GREEN, LOW);  }
  else                   { digitalWrite(LED_RED, LOW);  digitalWrite(LED_GREEN, HIGH); }

  // Serial log
  Serial.print("T="); Serial.print(temp, 1); Serial.print("C  ");
  Serial.print("H="); Serial.print(humidity, 1); Serial.println("%");

  // Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(temp, 1); lcd.write(223); lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum:  "); lcd.print(humidity, 1); lcd.print(" %");
}