#include "json.h"
char* msgDe(String input,const char* dName){

StaticJsonDocument<250> doc;
DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.f_str());
  return "Server Error";
}
const char* device = doc["device"]; // "ESP_1"

const char* status = doc["status"]; // "success"
const char* data = doc["data"]; // "Cai nay co \n Duoc khong?"
const char* type = doc["type"]; // "control"
//if (type == "control" && device == dName) 
  return (char*)data;
//Serial.println(device);
//Serial.println(status);
//Serial.println(data);
//Serial.println(type);
}
String datSe(String input){
  String output;
  StaticJsonDocument<96> doc;

  doc["device"] = "ESP_1";
  doc["data"] = input.c_str();
  doc["type"] = "control";

  serializeJson(doc, output);
  return output;
}
