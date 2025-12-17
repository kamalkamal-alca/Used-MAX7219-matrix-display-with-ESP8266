# Used-MAX7219-matrix-display-with-ESP8266
Display and scroll temperature, humidity, date and time on a max7219 LED matrix

if used esp8266 nodemcu: 
#define CLK_PIN   D5 // or SCK
#define DATA_PIN  D7 // or MOSI
#define CS_PIN    D6 //
//===================ESP-01====================
//#define CLK_PIN   0  // or SCK
//#define DATA_PIN  3  // or MOSI
//#define CS_PIN    1  // or SS
change for this command: 
//MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
