#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 6     
#define DHTTYPE DHT22 // Tipe sensor diubah ke DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi Pin Tambahan
int ledPin = 8;
float ambangSuhu = 30.0;

void setup() {
  Serial.begin(9600);
  
  // Memulai LCD
  lcd.init();
  lcd.backlight();
  
  dht.begin();

  // Pesan Awal
  lcd.setCursor(0, 0);
  lcd.print("Lcd Ready..");
  delay(2000);
  lcd.clear();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  
  delay(2000);

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!  ");
    return;
  }

  // Baris 1: Suhu
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); // Simbol derajat
  lcd.print("C   ");   

  // Baris 2: Kelembaban
  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(hum);
  lcd.print("%     ");

  if (temp > ambangSuhu) {
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(13, 0);
    lcd.print("HOT");
  } else {
    digitalWrite(ledPin, LOW);
    lcd.setCursor(13, 0);
    lcd.print("   ");       // clear tulisan HOT
  }
}
