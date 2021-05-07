#include "customHTTP.h"

String checkmsg = "{\"device\":\"ESP_1\",\"data\":\"\",\"type\":\"check\"}";
String controlmsg = "{\"device\":\"ESP_1\",\"data\":\"_data_\",\"type\":\"control\"}";
String errormsg ="{\"device\":\"ESP_1\",\"type\":\"control\",\"data\":\"error\"}";
char* serverName = "http://node.creta.work:1888/lcd/request";
String httpPost(char *_url, char *_dat){
  //Serial.println(_url);
  //Serial.println(_dat);
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(_url);

      // Specify content-type header
      //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      //String httpRequestData = "{\"data\":\"xin chao\"}";           
      // Send HTTP POST request
      //int httpResponseCode = http.POST(httpRequestData);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      int httpResponseCode = http.POST(_dat);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      return(http.getString());
        
      // Free resources
      http.end();
    }
    else {
      return "ERROR";
    }
}
