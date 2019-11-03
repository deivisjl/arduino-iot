#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define DHTPIN 0          // D3

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
long interval = 120000;
bool peticionTemperatura = false;

const char* ssid = "DESKTOP-VJKUJBV_2286";
const char* password = ">9Np9534";
const char* host = "165.227.203.69";

void setup() {
  Serial.begin(9600);
   dht.begin();

   WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  sensores();
}

void sensores(){

  char dato = Serial.read();
  switch(dato){
    case '2':{
      Serial.println("Recibi un 2");
      /***********Peticion de proximidad ****************/
                                WiFiClient client;

                                const int httpPort = 80;
                                
                                if(!client.connect(host, httpPort))
                                {
                                  Serial.println("Connection failed");
                                  return;
                                }
                              
                                String url = "/api/";
                                String proximidad ="proximidad";
                              
                                Serial.print("Realizando peticion: ");
                                Serial.println(url);
                              
                                client.print(String("GET ") + url + proximidad + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close \r\n\r\n");
                              
                                unsigned long timeout = millis();
                              
                                while (client.available() == 0){
                                  if(millis() - timeout > 5000){
                                    Serial.println(">>> Client Timeout !");
                                    client.stop();
                                    return;
                                   }  
                                }
                              
                                while(client.available()){
                                  String line = client.readStringUntil('\r');
                                  Serial.print(line);
                                }
      /**************************************************/
    }
    break;
    case '3':{
      Serial.println("Recibi un 3");

                                WiFiClient client;

                                const int httpPort = 80;
                                
                                if(!client.connect(host, httpPort))
                                {
                                  Serial.println("Connection failed");
                                  return;
                                }
                              
                                String url = "/api/";
                                String gas ="gas";
                              
                                Serial.print("Realizando peticion: ");
                                Serial.println(url);
                              
                                client.print(String("GET ") + url + gas + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close \r\n\r\n");
                              
                                unsigned long timeout = millis();
                              
                                while (client.available() == 0){
                                  if(millis() - timeout > 5000){
                                    Serial.println(">>> Client Timeout !");
                                    client.stop();
                                    return;
                                   }  
                                }
                              
                                while(client.available()){
                                  String line = client.readStringUntil('\r');
                                  Serial.print(line);
                                }
      /**************************************************/
    }
    break;
    case '4':{
      Serial.println("Recibi un 4");

      WiFiClient client;

                                const int httpPort = 80;
                                
                                if(!client.connect(host, httpPort))
                                {
                                  Serial.println("Connection failed");
                                  return;
                                }
                              
                                String url = "/api/";
                                String panico ="panico";
                              
                                Serial.print("Realizando peticion: ");
                                Serial.println(url);
                              
                                client.print(String("GET ") + url + panico + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close \r\n\r\n");
                              
                                unsigned long timeout = millis();
                              
                                while (client.available() == 0){
                                  if(millis() - timeout > 5000){
                                    Serial.println(">>> Client Timeout !");
                                    client.stop();
                                    return;
                                   }  
                                }
                              
                                while(client.available()){
                                  String line = client.readStringUntil('\r');
                                  Serial.print(line);
                                }
      /**************************************************/
    }
    break;
    default:
    break;
  }

  unsigned long currentMillis = millis();

  if((currentMillis - previousMillis) >= interval)
  {
      previousMillis = currentMillis; 

      if(peticionTemperatura == false){
        peticionTemperatura = true;
          
      float h = dht.readHumidity();
      float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
     
      if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }

                                WiFiClient client;

                                const int httpPort = 80;
                                
                                if(!client.connect(host, httpPort))
                                {
                                  Serial.println("Connection failed");
                                  return;
                                }
                              
                                String url = "/api/temperatura/show";
                                String temperatura = "?temperatura=";
                                String humedad = "&humedad=";
                              
                              
                                Serial.print("Realizando peticion: ");
                                Serial.println(url);
                              
                                client.print(String("GET ") + url + temperatura + t + humedad + h + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close \r\n\r\n");
                              
                                unsigned long timeout = millis();
                              
                                while (client.available() == 0){
                                  if(millis() - timeout > 5000){
                                    Serial.println(">>> Client Timeout !");
                                    client.stop();
                                    return;
                                   }  
                                }
                              
                                while(client.available()){
                                  String line = client.readStringUntil('\r');
                                  Serial.print(line);
                                }
        
        peticionTemperatura = false;
      }
            
   }
}
