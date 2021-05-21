#define configUSE_PREEMPTION 0

#include "customHTTP.h"
#include "espwifi.h"
#include "lcd.h"
#include "json.h"
#include "keypad.h"
String exmsg ="{\"device\": \"ESP_1\",\"data\": \"976\",\"type\":\"control\"}";
#include <WiFi.h>

void wifiTask(void *pvParameter);
void lcdTask(void *pvParameter);
void keypadTask(void *pvParameter);
void dataTask(void *pvParameter);

TaskHandle_t TaskHandle_1;
TaskHandle_t lTask;
TaskHandle_t d2Task;
TaskHandle_t dTask;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  //WiFi.begin("CRETA-KD-1","yoursolution");
  lcdInit();
  delay(5);
  dataDisp("Initializing...\nPlease wait");
  delay(50);
  wifiInit();
  
  xTaskCreate(wifiTask, "Task1", 4096, NULL, 1, NULL);
  
  //xTaskCreate(lcdTask, "Task2", 4096, NULL, 1, &lTask);
  
  xTaskCreate(keypadTask, "Task3", 5000, NULL, 2, NULL);
  
  dataDispLine(0,"All Done!!!     ");
  dataDispLine(1,WiFi.localIP().toString());
  
}
void loop() {
  //IDLE
  Serial.print("");
  vTaskDelay(100/portTICK_PERIOD_MS);
}
void wifiTask(void *pvParameter)
{
  //declare here
  for(;;){
//    if (millis()%10000<5)
      if (WiFi.status()!=WL_CONNECTED) WiFi.begin();
//    if (millis()%60000<5)
//      do{
//        res = httpPost(serverName,checkmsg);
//        //Serial.println(res);
//        vTaskDelay(50/portTICK_PERIOD_MS);
//      }while(!res.indexOf("success"));
      
      vTaskDelay(60000/portTICK_PERIOD_MS);
      //xTaskCreate(lcdTask, "Task2", 4096, NULL, 2, &lTask);
      xTaskCreate(dataTask,"DataSendTask",4096,(void *) 1, 9, &d2Task);
      
  }
}
bool send =false;
bool lcdRun = false;
String input="";
String res="";
void lcdTask(void *pvParameter){
  //declare here
//  char *res;
//  res = (char *) pvParameter;
  
  for(;;){
    lcdRun=true;
    if (input.length()>=0){
      
      if (input.length()==1){
          //lcdClear();
          //lcdInit();
//          dataDispLine(1,input);
          dataDisp("INPUT DATA:     \n                ");
          dataDispLine(1,input);
          //dataDispLine(0,"INPUT DATA");
          //lcdInit();
          //dataDispLine(0,"INPUT DATA");
          //dataDispLine(1,input);
          
          
          
          
      } else
      dataDispLine(1,input);
      
      //heap_caps_dump_all();
      //Serial.println(input);
      }
    if (res!=""){
      //Serial.println(res);
      if (!dataDisp(res)) dataDisp("Respose Error \nPlease Re-Enter");
      res ="";
        //xTaskCreate(dataTask,"DataSendTask",4096,(void *) 2, 9, &dTask);
    }

      //dataDispLine(1,input);
    //vTaskDelay(1/portTICK_PERIOD_MS);
    lcdRun=false;
    vTaskDelete(lTask);
  }
}

void keypadTask(void *pvParameter){
  //declare here
  send = false;
  for(;;){
    char ckey = keyGet();
    if (ckey){
      
      //Serial.println(ckey);
      if (ckey =='#') {
        xTaskCreate(dataTask,"DataSendTask",4096,(void *) 0, 3, &dTask);
      } 
      else if (ckey =='A' || ckey =='B'|| ckey =='C'){
          if (ckey=='A') lcdInit();
        
         }
      else if (ckey =='D'){
        ESP.restart(); 
      }else{

        if (ckey >='0' && ckey<='9') {
          input+=String(ckey);
        }
        if (ckey =='*') 
          if (input.length()>0)input.remove(input.length()-1);
          
        if (!lcdRun) {
        xTaskCreate(lcdTask, "Task2", 4096, NULL, 5, &lTask);
        }
      }
      //if (input[15]=='\0') input=(String)"";
    }
    vTaskDelay(100/portTICK_PERIOD_MS);  
  }}
void dataTask(void *pvParameter){
  //declare here
  int  CMD;
  CMD = (int)pvParameter;
  String cmsg;
  String _res;
  for(;;){
    if (CMD==0){
      cmsg = datSe(input);
      input=(String)"";
    }else if (CMD ==1){
      cmsg = checkmsg;
    }else if (CMD ==2){
      cmsg = errormsg;
    }
    _res = httpPost(serverName,&cmsg[0]);
    if (_res.indexOf("ERROR")){
      //do something
    }
    if (_res.indexOf("success"))
      if (_res.indexOf("control")){
        Serial.println(_res);
        res = msgDe(_res,"ESP_1");
//        Serial.println(_res);
//        Serial.println(res);
       //dataDisp(res);
        //delay(1000);
        xTaskCreate(lcdTask, "Task2", 4096, NULL, 1, &lTask);
//      if (!dataDisp(res))
//        dataDisp("Data Error");
//      //Serial.println(res);
      }
    vTaskDelete(d2Task);
    vTaskDelete(dTask);
  }
}
