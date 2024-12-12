#include <JDateLib.h>
#include <NTPClient.h>
#include <EBigNum.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ArduinoOTA.h>
#include <ElegantOTA.h>
#include <ESP8266mDNS.h>
const char *ssid = "";
const char *password = "";
const char *ssid0 = "";
const char *password0 = "";
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String months[12]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
LiquidCrystal_I2C lcd(0x27, 16, 2);
ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 12600);
EBigNum EBN(&lcd);

boolean BackLight = true;
#define BuzzerPin D11
void setup() {Buzzer(200,1,false);Load();}
void loop() {softWareLoop();ShowClock();}