#include "DHT.h"
#include <LiquidCrystal.h> 
#include <Servo.h>

#define DHTPIN A1
#define DHTYPE DHT11
#define ledPin 22

Servo myservo; 
DHT dht(DHTPIN, DHTYPE);

LiquidCrystal lcd(1, 2, 4, 5, 6, 7 );

float Temp = 30;
float hum = 80;
int pos_servo = 0; 

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  lcd.begin(16,2);
  //lcd.setCursor(0,0);
  dht.begin();
  
  pinMode(ledPin,0);
  myservo.attach(24); 
}

void loop() {
  // put your main code here, to run repeatedly:
 float t = dht.readTemperature(); 
 float h = dht.readHumidity();
 
  myservo.write(0);
  digitalWrite(ledPin, 0);

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t,1);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(h,1);
  lcd.print(" %");

  /*if (t>Temp){
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
        //myservo.write(90);
        //delay(5000); 
        //myservo.write(pos_servo);
        
      } else {
        digitalWrite(2,LOW); 
      }
    }
  }*/

if(t > Temp && h < hum) {
  digitalWrite(ledPin, 1); 
  myservo.write(90);
  delay (2000);
  myservo.write(0);
} else 
  if (t > Temp && h > hum ){
    digitalWrite(ledPin, 1);
    myservo.write(0);
    delay (2000);
    myservo.write(0);
    }
   else 
    if (t < Temp && h < hum) {
      digitalWrite(ledPin, 0); 
      myservo.write(90); 
      delay (2000);
      myservo.write(0);
    }
   else 
    if (t < Temp && h > hum){
      digitalWrite(ledPin, 0); 
      myservo.write(0); 
      delay (2000);
      myservo.write(0);
    }
  

  
  delay(1000);
  lcd.clear();
}
