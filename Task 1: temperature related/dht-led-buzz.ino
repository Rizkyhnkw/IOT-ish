#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 6     
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

int ledPin = 8;
int buzzerPin = 5;
float ambangSuhu = 30.0;

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Lcd Ready..");
  delay(2000);
  lcd.clear();

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
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

  if (temp > ambangSuhu) {
    // Tampilan Overheat 
    lcd.print("!!! WARNING !!! "); 
    lcd.setCursor(0, 1);
    lcd.print("OVERHEAT: ");
    lcd.print(temp);
    lcd.print("C ");

    digitalWrite(ledPin, HIGH); 
    tone(buzzerPin, 1000);
  } else {

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("C       "); 

    lcd.setCursor(0, 1);
    lcd.print("Hum : ");
    lcd.print(hum);
    lcd.print("%        "); 

    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }
}
