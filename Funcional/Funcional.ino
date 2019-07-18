#include "DHT.h"
#include <LiquidCrystal.h> 
#define DHTPIN A1
#define DHTYPE DHT11

#define ledPin 22

DHT dht(DHTPIN, DHTYPE);

LiquidCrystal lcd(1, 2, 4, 5, 6, 7 );

float Temp = 30;
float hum = 60;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  lcd.begin(16,2);
  //lcd.setCursor(0,0);
  dht.begin();
  
  pinMode(ledPin,0);
}

void loop() {
  // put your main code here, to run repeatedly:
 float t = dht.readTemperature(); 
 float h = dht.readHumidity();


  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t,1);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(h,1);
  lcd.print(" %");


  if (t>Temp){
    digitalWrite(ledPin, 1);
  } else {
    if (t < Temp) {
      digitalWrite(22, LOW);
      digitalWrite(11, LOW);
      //digitalWrite(2,LOW); 
      digitalWrite(13, HIGH);
    }

    else {
      if (h < hum) {
        digitalWrite(2, HIGH);
        
      } else {
        digitalWrite(2,LOW); 
      }
    }
  }
  delay(1000);
  lcd.clear();
}
