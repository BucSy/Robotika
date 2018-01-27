#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int ledPin = 2;
const int potmeter = A0;
const int dcMotor1 = 3;
const int dcMotor2 = 7;
const int engedelyezoPort = 10;
float homerseglet;
float paratartalom;
int potmeterErtek = 0;
int currentState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(potmeter, INPUT);
  pinMode(dcMotor1, OUTPUT);
  pinMode(dcMotor2, OUTPUT);
  pinMode(engedelyezoPort, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  switch(currentState) {
    case 0:               //nyugalmi
      Serial.println("nullas");
      digitalWrite(ledPin, LOW);
      if (analogRead(potmeter) > 0) {
        homerseglet = analogRead(potmeter);
      } else {
        homerseglet = dht.readTemperature();
      }
      paratartalom = dht.readHumidity();
      Serial.println(homerseglet);
      Serial.println(paratartalom);
      digitalWrite(engedelyezoPort, LOW);
      digitalWrite(dcMotor1, HIGH);
      digitalWrite(dcMotor2, LOW);
      delay(50);
      digitalWrite(dcMotor1, LOW);
      digitalWrite(dcMotor2, HIGH);
      if (homerseglet < 20 && paratartalom > 40) {
        currentState = 2;
        break;
      }
      if (homerseglet < 20) {
        currentState = 1;
        break;
      }
      if (paratartalom > 40) {
        currentState = 3;
        break;
      }
      break;
    case 1:               //fűtés
      Serial.println("egyes");
      digitalWrite(ledPin, HIGH);
      if (analogRead(potmeter) > 0) {
        homerseglet = analogRead(potmeter);
      } else {
        homerseglet = dht.readTemperature();
      }
      paratartalom = dht.readHumidity();
      Serial.println(homerseglet);
      Serial.println(paratartalom);
      digitalWrite(engedelyezoPort, LOW);
      digitalWrite(dcMotor1, HIGH);
      digitalWrite(dcMotor2, LOW);
      delay(50);
      digitalWrite(dcMotor1, LOW);
      digitalWrite(dcMotor2, HIGH);
      if (paratartalom < 40 && homerseglet > 20) {
        currentState = 0;
        break;
      }
      if (paratartalom > 40) {
        currentState = 3;
        break;
      }
      if (paratartalom > 40 && homerseglet < 20) {
        currentState = 2;
        break;
      }
      if (homerseglet > 20) {
        currentState = 0;
        break;
      }
      break;
    case 2:           //fűtés & paratartalom
      Serial.println("kettes");
      digitalWrite(ledPin, HIGH);
      if (analogRead(potmeter) > 0) {
        homerseglet = analogRead(potmeter);
      } else {
        homerseglet = dht.readTemperature();
      }
      paratartalom = dht.readHumidity();
      Serial.println(homerseglet);
      Serial.println(paratartalom);
      //motor
      digitalWrite(engedelyezoPort, HIGH);
      digitalWrite(dcMotor1, HIGH);
      digitalWrite(dcMotor2, LOW);
      delay(50);
      digitalWrite(dcMotor1, LOW);
      digitalWrite(dcMotor2, HIGH);
      if (paratartalom < 40 && homerseglet > 20) {
        currentState = 0;
        break;
      }
      if (paratartalom > 40 && homerseglet > 20) {
        currentState = 3;
        break;
      }
      if (paratartalom < 40 && homerseglet < 20) {
        currentState = 1;
        break;
      } 
      break;
    case 3:             //magas páratartalom
      Serial.println("harmas");
      digitalWrite(ledPin, LOW);
      if (analogRead(potmeter) > 0) {
        homerseglet = analogRead(potmeter);
      } else {
        homerseglet = dht.readTemperature();
      }
      paratartalom = dht.readHumidity();
      Serial.println(homerseglet);
      Serial.println(paratartalom);
      //motor
      digitalWrite(engedelyezoPort, HIGH);
      digitalWrite(dcMotor1, HIGH);
      digitalWrite(dcMotor2, LOW);
      delay(50);
      digitalWrite(dcMotor1, LOW);
      digitalWrite(dcMotor2, HIGH);
      if (paratartalom < 40 && homerseglet > 20) {
        currentState = 0;
        break;
      }
      if (paratartalom > 40 && homerseglet < 20) {
        currentState = 2;
        break;
      }
      if (paratartalom < 40 && homerseglet < 20) {
        currentState = 1;
        break;
      }
      break;
  }
}
