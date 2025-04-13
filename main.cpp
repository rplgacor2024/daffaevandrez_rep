  #include <ESP8266WiFi.h>
  /*#include <BlynkSimpleEsp8266.h>

  #define BLYNK_PRINT Serial

  //blynk information
  char auth[] = "token blynk";
  char ssid[] = "Sweet Home";
  char pass[] = "2317141025";
  */
  int soilPin = A0;
  int soilValue;

  void setup () {
    Serial.begin(115200);
    /*Blynk.begin(auth, ssid, pass);*/
    pinMode(soilPin, INPUT);
  }

  void loop (){

    soilValue = analogRead(soilPin);
    int kelembapan = map(soilValue, 1023,0 ,0 ,100);  

    Serial.print("tingkat kelembapan : "));
    Serial.print(kelembapan);
    Serial.print("%");

    /*Blynk.virtualWrite (V1, kelembapan);*/
    delay(1000);
  }