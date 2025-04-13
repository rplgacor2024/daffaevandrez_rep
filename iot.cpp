#define BLYNK_TEMPLATE_ID           "TMPL6h4nCjjAp"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "81yn4tD4KPmXBuBS3ezftkKjWPdNYJTy"
#define BLYNK_PRINT Serial

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
char auth[] = "81yn4tD4KPmXBuBS3ezftkKjWPdNYJTy";
char ssid[] = "Galaxy A03 2e90";
char pass[] = "zen12345";


int soilpin = A0;
int soilvalue;
int ledt = D1;
int ledf = D2;

byte flower[8] = {
  0b00100,
  0b10101,
  0b01110,
  0b11111,
  0b01110,
  0b10101,
  0b00100,
  0b00000
};


void setup (){


Serial.begin(115200);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
pinMode (soilpin, INPUT);
pinMode (ledt, OUTPUT);
pinMode (ledf, OUTPUT);

String text="O   v   O";
int position = (16 - text.length())/2; 
Wire.begin(D3, D4);
lcd.begin(16, 2);
lcd.backlight();
lcd.setCursor(position, 0);
lcd.print(text);
lcd.setCursor(position, 1);
lcd.print("Hi am planty");
delay(5000);

lcd.createChar(0, flower);  
}

unsigned long eyeprev=0;
const unsigned long eyeinterval= 500;
static bool openeye= true;

int rposition = 0; 


void loop () {

  static bool ledState = LOW;
  static unsigned long prevMillis = 0;
  const int interval = ledState ? 10 : 3000;; 


  soilvalue = analogRead(soilpin);
  int kelembapan = map (soilvalue, 1023, 0, 0, 100);
  Serial.print ("Kelembapan saat ini : ");
  Serial.print (kelembapan);
  Serial.print ("%");
  Serial.println ();


if (kelembapan >= 30 && millis() - prevMillis >= interval) {

  prevMillis = millis();
  ledState = !ledState;  // Balik kondisi LED
  digitalWrite(ledt, ledState);
  Blynk.virtualWrite(V5, "--💧Your plant are still hydrated💧--(online)");
  
  lcd.backlight();
  if (millis() - eyeprev >= eyeinterval){

    eyeprev =millis();
    openeye = !openeye;
  }

  
  String text2=openeye ? "^   v   ^": "O   v   O";
  String rtext2="Your plant happy, hydrated " + String(kelembapan) + "%";
  int position = (16 - text2.length())/2; 

  lcd.setCursor(position, 0);
  lcd.print (text2);
  lcd.setCursor(15, 0);
  lcd.write(byte(0));
  String otext2=rtext2.substring (rposition, rposition + 16);
  lcd.setCursor(0, 1 );
  lcd.print(otext2);

  

  

  rposition++;
  if (rposition > rtext2.length() -16) {
    rposition = 0;
  }
  delay(1000);
}

else {
  digitalWrite (ledt, LOW);
  delay(10);
}

if (kelembapan < 30 && millis() - prevMillis >= interval) {
    prevMillis = millis();
    ledState = !ledState;  // Balik kondisi LED
    digitalWrite(ledf, ledState);
    Blynk.virtualWrite(V5, "--❗️🔥your plants are dry🔥❗️--(online)");
    
    lcd.backlight();

    if (millis () - eyeprev >= eyeinterval){
      openeye = !openeye;
    }
    String text3=openeye? ">   O   <":"T   O   T";
    String rtext3="Your plant NOT happy, hydrated " + String(kelembapan) + "% ";
    int position = (16 - text3.length())/2; 
    lcd.setCursor(position, 0);
    lcd.print (text3);
    lcd.setCursor(15, 0);
    lcd.write(byte(0));
    String otext3=rtext3.substring (rposition, rposition + 16);
    lcd.setCursor(0, 1 );
    lcd.print(otext3);

  

  rposition++;
  if (rposition > rtext3.length() -16) {
    rposition = 0;
}
  delay(1000);
}
else {
  digitalWrite(ledf, LOW);
  delay(10);
}

if (kelembapan < 1 ) {

  Blynk.virtualWrite(V4, 0);
  digitalWrite(ledf, LOW);
  Blynk.virtualWrite(V5, "--💤Your hydrate system ofline💤--");
  Serial.println("--💤Your hydrate system ofline💤--");
  delay(3000);

  while(kelembapan < 1){
    lcd.clear();
    lcd.noBacklight();
    delay(3000);
    Blynk.virtualWrite (V8, "Tips");
    delay(3000);
    Blynk.virtualWrite (V8, "if your system were offline, makesure you put the sensor corectly");
    delay(3000);
    Blynk.virtualWrite (V8, "and makesure your plant its preety wet");
    delay(5000);
    soilvalue = analogRead(soilpin);
    kelembapan = map(soilvalue, 1023, 0, 0, 100);

  }
}


Blynk.virtualWrite (V4, kelembapan);
Blynk.virtualWrite (V7, "current humidity : ");


Blynk.run();
delay(100);

  
}