#include "lcd.h"
LiquidCrystal_I2C lcd(0x27,16,2); 
void lcdInit(){
  lcd.begin();
  //vTaskDelay(1/portTICK_PERIOD_MS);            
  lcd.backlight();
}
void lcdClear(){
  lcd.clear();
}
bool charDisp(char ch){
  lcd.print(ch);
  //vTaskDelay(0.1/portTICK_PERIOD_MS);
}
bool dataDisp(String dat){
  char *_dat = &dat[0];
  return dataDisp(_dat);
}
bool dataDispLine(int line,String dat){
  char *_dat = &dat[0];
  return dataDispLine(line,_dat);
}
bool dataDispLine(int line,char *dat){
  int _counter =0;
  lcd.setCursor(0,line);
  lcd.print("                ");
  //vTaskDelay(2/portTICK_PERIOD_MS); 
  lcd.setCursor(0,line);
  //vTaskDelay(1/portTICK_PERIOD_MS); 
  while(*dat){
    lcd.print(*dat);
    vTaskDelay(1/portTICK_PERIOD_MS);
    dat++;
    _counter++;
    if (_counter>16) {
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("Server Error");
      return false;
    }
  }
  return true;
}
bool dataDisp(char *dat){
  lcdInit();
  lcd.clear();
  //vTaskDelay(1/portTICK_PERIOD_MS); 
  int _counter =0;
  lcd.setCursor(0,0);
  //vTaskDelay(0.1/portTICK_PERIOD_MS); 
  while(*dat){
    if (*dat=='\n') {
      lcd.setCursor(0,1);
      //vTaskDelay(0.1/portTICK_PERIOD_MS); 
      _counter = 0;
    }
    else {
      lcd.print(*dat);
      //vTaskDelay(0.1/portTICK_PERIOD_MS); 
    }
    dat++;
    _counter++;
    if (_counter>16) {
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("Server Error");
      return false;
    }
  }
  return true;
}
bool enough(String st){
  int _tmp = 0;
  for (int i=0;i<st.length();i++){
    if (st[i]=='\n') _tmp =0;
    else
      _tmp++;
    if (_tmp>16) return false;
  }
  return true;
}
/*
void loop()
{
  delay(1000);
  String st = "Xin chao tat ca cac ban nhe \n hello moto???";
  dataDisp(&st[0]);
  delay(1000);
  dataDisp("hahahahaha");
}*/
