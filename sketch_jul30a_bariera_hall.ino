#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>

const int irPin=2;
const int controlPin=7;
const int buzzerPin=4;
const int rosuPin=6;
const int verdePin=3;
const int albsPin=5;
const int WCS1600_PIN=A0;
const int pasirotire90=512;
const float sensibilitate=0.022;
const float vRef=2.5;
const float intVref=5.0;
const float ADC_RES = 4095.0; // mod 12 biti

const int adresaEEPROM = 0;
bool pozitie90=false;
float curent=0.0;
int stareir=HIGH;
int contorTreceri=0;
String stareActuala="Start";

#define lecran 128
#define hecran 64
Adafruit_SSD1306 oled(lecran, hecran, &Wire, -1);

Stepper motor=Stepper(2048, 8, 10, 9, 11);

void setup() {
  pinMode(irPin, INPUT_PULLUP);
  pinMode(controlPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(rosuPin, OUTPUT);
  pinMode(verdePin, OUTPUT);
  pinMode(albsPin, OUTPUT);

  digitalWrite(controlPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(verdePin, LOW);
  digitalWrite(rosuPin, LOW);
  digitalWrite(albsPin, LOW);

  Serial.begin(9600);
  delay(1000);
  motor.setSpeed(10);
  analogReference(AR_DEFAULT); //ref scara 5V
  analogReadResolution(12); // precizie foarte mare 12 biti
  delay(2000);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0X3C)){
    Serial.println(F("SS1306 allocation failed"));
    while(true);
  }
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.display();

  EEPROM.get(adresaEEPROM, contorTreceri);
  if(contorTreceri<0 || contorTreceri>3200){
    contorTreceri=0;
    EEPROM.put(adresaEEPROM, contorTreceri);
  } 

  while(Serial.available()>0){
    Serial.read();
  }
  Serial.println("Doresti resetarea memoriei?(da/nu)");

  oled.setCursor(0, 0);
  oled.print("Doresti resetarea");
  oled.setCursor(0, 9);
  oled.print("memoriei?");
  oled.display();
  delay(2000);

  oled.setCursor(0, 30);
  oled.print("Raspuns (da/nu):");
  oled.display();

  while (Serial.available() == 0) {} //astept pana se apasa Enter

  String raspuns=Serial.readStringUntil('\n');
  raspuns.trim();
  Serial.println(raspuns);

  if(raspuns=="da"){
    contorTreceri=0;    
    EEPROM.put(adresaEEPROM, contorTreceri);
    while(Serial.available()>0){
      Serial.read();
    }
  }
  oled.setCursor(100, 30);
  oled.print(raspuns);  
  oled.display();
  delay(3000);  
}

void oledDisplayHeader(){
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print("Stare: ");
  oled.print(stareActuala);
  oled.setCursor(0, 28);
  oled.print("Numar treceri: ");
  oled.print(contorTreceri);
  oled.setCursor(0, 57);
  oled.print("Valoare curent: ");
  oled.print(curent);
  oled.print("A");
  oled.display();
}


float readWCS1600Current(){
  long sumaADC=0;
  int numarEsant=100;
  for(int i=0; i<numarEsant; i++){
    sumaADC=sumaADC+analogRead(WCS1600_PIN);
    delayMicroseconds(500);
  }
  float medADC=(float)sumaADC/numarEsant;
  float tens=medADC*(intVref/ADC_RES);
  float curent=(tens-vRef)/sensibilitate;
  return abs(curent);
  
}

void oprireAlim(){
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  digitalWrite(controlPin, LOW);
}

void loop() {
  oledDisplayHeader();
  stareir=digitalRead(irPin);
  if(stareir==LOW && pozitie90==false){
    contorTreceri++;
    EEPROM.put(adresaEEPROM, contorTreceri);
    Serial.println("Obiect detectat");
    digitalWrite(controlPin, HIGH);
    motor.step(pasirotire90);
    delay(250);
    curent=readWCS1600Current()/10;
    oprireAlim();
    pozitie90=true;
    Serial.print("Curent: ");
    Serial.println(curent);
    Serial.println(contorTreceri);
    if(curent<0.15){
      stareActuala="Curent mic";
      digitalWrite(verdePin, HIGH);
      delay(500);
      digitalWrite(verdePin, LOW);
    }else if(curent>=0.15 && curent<=0.45){
      stareActuala="In siguranta";      
      digitalWrite(albsPin, HIGH);
      delay(500);
      digitalWrite(albsPin, LOW);
    }else if(curent>0.45){
      stareActuala="Atentie!";
      digitalWrite(rosuPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(rosuPin, LOW);
      digitalWrite(buzzerPin,LOW);
    }
  }else if(pozitie90==true && stareir==HIGH){
    Serial.println("Obiectul a trecut");
    digitalWrite(controlPin, HIGH);
    motor.step(-pasirotire90);
    delay(250);
    pozitie90=false;
    curent=readWCS1600Current()/10;
    oprireAlim();
    Serial.print("Curent: ");
    Serial.println(curent);
    if(curent<0.15){
      stareActuala="Curent mic";
      digitalWrite(verdePin, HIGH);
      delay(500);
      digitalWrite(verdePin, LOW);
    }else if(curent>=0.15 && curent<=0.45){
      stareActuala="In siguranta";
      digitalWrite(albsPin, HIGH);
      delay(500);
      digitalWrite(albsPin, LOW);
    }else if(curent>0.45){
      stareActuala="Atentie!";
      digitalWrite(rosuPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(rosuPin, LOW);
      digitalWrite(buzzerPin,LOW);
    }
  }
  delayMicroseconds(500);
}