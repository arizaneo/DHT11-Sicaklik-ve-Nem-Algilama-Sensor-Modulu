#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// LCD için I2C adresi (0x27 ya da 0x3F olabilir)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("DHT11 Sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(2000); // DHT11 her 2 saniyede bir ölçüm yapar

  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();

  if (isnan(nem) || isnan(sicaklik)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Veri Hatasi!");
    Serial.println("DHT11 sensöründen veri okunamadı!");
    return;
  }

  // --- LCD EKRAN ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nem: ");
  lcd.print(nem);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Sicaklik: ");
  lcd.print(sicaklik);
  lcd.print("C");

  // --- SERI MONITOR ---
  Serial.print("Nem: ");
  Serial.print(nem);
  Serial.print(" %  |  Sicaklik: ");
  Serial.print(sicaklik);
  Serial.println(" *C");
}
