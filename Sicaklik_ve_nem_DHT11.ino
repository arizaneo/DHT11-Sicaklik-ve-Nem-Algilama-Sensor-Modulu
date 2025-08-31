#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2      // DHT11'in DATA pini Arduino'nun D2 pinine bağlı
#define DHTTYPE DHT11 // Sensör tipi

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Sıcaklık ve Nem Ölçümü");
  dht.begin();
}

void loop() {
  delay(2000);

  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();

  if (isnan(nem) || isnan(sicaklik)) {
    Serial.println("DHT11 sensöründen veri okunamadı!");
    return;
  }

  Serial.print("Nem: ");
  Serial.print(nem);
  Serial.print(" %  |  Sicaklik: ");
  Serial.print(sicaklik);
  Serial.println(" *C");
}
