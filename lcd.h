#ifndef _lcd__h_
#define _lcd__h_

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
 

void lcdInit();
bool dataDisp(char *dat);
bool dataDisp(String dat);
bool dataDispLine(int line,String dat);
bool dataDispLine(int line,char *dat);
bool enough(String st);
#endif
