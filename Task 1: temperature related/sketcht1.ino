#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11
#define LEDPIN 6
#define BUZZPIN 9
#define BATAS_SUHU 31

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZPIN, OUTPUT);
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca sensor!");
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.print("°C  |  Kelembaban: ");
  Serial.print(humidity);
  Serial.println("%");

  if (temperature > BATAS_SUHU) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(BUZZPIN, HIGH);
    Serial.println("PERINGATAN: Suhu tinggi!");
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(BUZZPIN, LOW);
  }
}
