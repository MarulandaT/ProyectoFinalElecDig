//Llamado a librerias nececesarias
#include "DHT.h"
#include <LiquidCrystal.h> 
#include <Servo.h>

//Definición de parametros
#define DHTPIN A1
#define DHTYPE DHT11
#define ledPin 22

//Elementos a utilizar y sus puertos
Servo myservo; 
DHT dht(DHTPIN, DHTYPE);
LiquidCrystal lcd(1, 2, 4, 5, 6, 7 );

//Temperatura y humedad relativa para el invernadero
float Temp = 30;
float hum = 90;

void setup() {
  // put your setup code here, to run once:
  //Inicializacion de componentes
  lcd.begin(16,2);
  dht.begin();
  pinMode(ledPin,0);
  myservo.attach(24); 
}

void loop() {
  // put your main code here, to run repeatedly:
 
 //Parametros a leer desde el sensor
 float t = dht.readTemperature(); 
 float h = dht.readHumidity();

 //Estados iniciales del led y serv
  myservo.write(180);
  digitalWrite(ledPin, 0);

//Imprimir informacion por pantalla
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t,1);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(h,1);
  lcd.print(" %");

//Definicion de posibles casos entre temperatura y humedad para dar determinismo
if(t > Temp && h < hum) {
  digitalWrite(ledPin, 1); 
  myservo.write(180);
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
      myservo.write(180); 
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
