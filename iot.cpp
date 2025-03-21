#define BLYNK_TEMPLATE_ID           "TMPL6h4nCjjAp"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "81yn4tD4KPmXBuBS3ezftkKjWPdNYJTy"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "81yn4tD4KPmXBuBS3ezftkKjWPdNYJTy";
char ssid[] = "Sweet Home";
char pass[] = "2317141025";


int soilpin = A0;
int soilvalue;
int ledt = D1;
int ledf = D2;

void setup (){


Serial.begin(115200);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
pinMode (soilpin, INPUT);
pinMode (ledt, OUTPUT);
pinMode (ledf, OUTPUT);



}

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
  delay(10);
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
    delay(10);
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
delay(2000);

  
}