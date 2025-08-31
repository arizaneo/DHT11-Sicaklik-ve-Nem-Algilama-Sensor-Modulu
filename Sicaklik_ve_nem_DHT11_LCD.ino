#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// LCD için I2C adresi (çoğu modül için 0x27, bazıları için 0x3F olabilir)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("DHT11 Sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(2000); // DHT11 yavaş ölçüm yapıyor

  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();

  if (isnan(nem) || isnan(sicaklik)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Veri Hatasi!");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nem: ");
  lcd.print(nem);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Sicaklik: ");
  lcd.print(sicaklik);
  lcd.print("C");
}
