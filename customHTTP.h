#ifndef _customHTTP__h_
#define _customHTTP__h_
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

extern String checkmsg;
extern String controlmsg;
extern String errormsg;
extern char* serverName;





String httpPost(char *_url, char *_dat);

#endif
