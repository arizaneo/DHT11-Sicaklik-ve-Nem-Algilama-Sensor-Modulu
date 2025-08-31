#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>
#include <virtuabotixRTC.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RTC (CE, IO, SCLK) → Arduino (6,7,8)
virtuabotixRTC myRTC(6, 7, 8);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  dht.begin();

  // RTC ayarı (ilk kurulumda aktif et, sonra yoruma al)
  // rtc.setDS1302Time(0, 0, 12, 7, 31, 8, 2025); 
  // saniye, dakika, saat, gün (1=PAZAR), tarih, ay, yıl

  lcd.setCursor(0, 0);
  lcd.print("DHT11 + RTC+ Saat");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(2000);

  myRTC.updateTime(); // RTC’den anlık zamanı güncelle

  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();

  if (isnan(nem) || isnan(sicaklik)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Veri Hatasi!");
    Serial.println("DHT11 sensöründen veri okunamadi!");
    return;
  }

  // --- LCD Ekran ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nem: ");
  lcd.print(nem);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Sicaklik: ");
  lcd.print(sicaklik);
  lcd.print("C");

  // --- Seri Monitör (Tarih / Saat ile Log) ---
  Serial.print(myRTC.dayofmonth);
  Serial.print("-");
  Serial.print(myRTC.month);
  Serial.print("-");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.print(myRTC.seconds);

  Serial.print("  |  Nem: ");
  Serial.print(nem);
  Serial.print("%  Sicaklik: ");
  Serial.print(sicaklik);
  Serial.println("C");
}
