#include "espwifi.h"
WiFiMulti wifiMulti;
void wifiInit(){
  wifiMulti.addAP("CRETA-KD-1","yoursolution");
  wifiMulti.addAP("CRETA-REF","yoursolution");
  wifiMulti.addAP("CRETA-KD","yoursolution");
  wifiMulti.addAP("TOTO9_5G","DATNK2015");
  Serial.println("Connecting Wifi");
  
  while(wifiMulti.run() != WL_CONNECTED) {
    vTaskDelay(1000/portTICK_PERIOD_MS);
    if (millis()>20000) ESP.restart();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
