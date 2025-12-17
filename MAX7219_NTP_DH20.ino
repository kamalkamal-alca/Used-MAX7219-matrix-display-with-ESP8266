#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <MD_Parola.h>         // https://github.com/MajicDesigns/MD_Parola
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "DHT20.h"    //library dht20 with i2c protocol

DHT20 DHT;

#define  DEBUG  1

#if  DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)

#endif
//------------------------------------------------------
//#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW//PAROLA_HW//GENERIC_HW
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
//===================NODEMCU===================
#define CLK_PIN   D5 // or SCK
#define DATA_PIN  D7 // or MOSI
#define CS_PIN    D6 //
//===================ESP-01====================
//#define CLK_PIN   0  // or SCK
//#define DATA_PIN  3  // or MOSI
//#define CS_PIN    1  // or SS

//MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 25;    // default frame delay value
textEffect_t scrollEffect  = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 100;  // in milliseconds

#define    BUF_SIZE    180
char curMessage[BUF_SIZE] = { "" };
char newMessage[BUF_SIZE] = { "" };
bool newMessageAvailable  = true;

int temp_c,temp_f, humid;

const char *ssid     = "VIRGIN102";
const char *password = "D67C6A3223A6C76D";

const long utcOffsetInSeconds = -18000;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() 
  {
  myDisplay.begin();
  myDisplay.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  Wire.begin();
  DHT.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {delay ( 500 );Serial.print ( "." );}
  timeClient.begin();
  myDisplay.setIntensity(0);
  myDisplay.displayClear();
  }

void loop() 
  {
  timeClient.update();
  Serial.print("Time       : ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  
  int status = DHT.read();
  temp_c = DHT.getTemperature();
  humid  = DHT.getHumidity();
  temp_f = 1.8*temp_c+32;
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(DHT.getTemperature(), 1);
  Serial.print((int)round(1.8*temp_c+32));

  char data[180];
  String bufferr;
  bufferr = "TEMP_C: " + (String)temp_c + "C TEMP_F: " + (String)temp_f + "F HUMI: " + (String)humid + "% TIME: " +(String)timeClient.getHours() + ":" +(String)timeClient.getMinutes();
  bufferr.toCharArray(data, 180);
  strcpy(curMessage, data);
  displayHandle();
  delay(1);
  }

  void displayHandle() 
  {
  if (myDisplay.displayAnimate()){myDisplay.displayReset();}
  }
