#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>;
#include <Wire.h>
#include <Adafruit_ADS1015.h>


#define FIREBASE_HOST "smart-india-hackathon-harshit.firebaseio.com"
#define FIREBASE_AUTH "bcMEsNxHijOr75VEuLHyTx3nSR0g1VIA2j3o5abV"


#define WIFI_SSID "HARSHIT"
#define WIFI_PASSWORD "12345678"


Adafruit_ADS1115 ads(0x48);


#define DHTPIN D7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);




void setup() {

//  float hum;
//  float temp;
//  int IR
  
  Serial.begin(115200);
  dht.begin();
  ads.begin();

  pinMode(D3,OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
}

void loop() {
 
    int LDR = ads.readADC_SingleEnded(0);
  
    Serial.print("Light Intensity: ");
    Serial.println(LDR, DEC);
    
    Firebase.setInt("LDR", LDR);

    float hum = dht.readHumidity();
    float temp= dht.readTemperature();
    
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    
    Firebase.setFloat("Temp", temp);
    Firebase.setFloat("Humidity", hum);

    int gas = analogRead(A0);       
    Serial.print("AirQua=");
    Serial.print(gas, DEC);           
    Serial.println(" PPM");
    Firebase.setInt("Air_Quality", gas);

    Serial.println(".");
    Serial.println(".");
    Serial.println(".");

    char LDR_OUT = Firebase.getInt("LDROUT");
    Serial.print("LDR OUT: ");
    Serial.println(LDR_OUT, DEC);
    
    if(LDR_OUT == 0)
      digitalWrite(D3,LOW);
    if(LDR_OUT == 1)
      digitalWrite(D3,HIGH);
      
    Serial.println(".");
    Serial.println(".");
        
    delay(10);
}
