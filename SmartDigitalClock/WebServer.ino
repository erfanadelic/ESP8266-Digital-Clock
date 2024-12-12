void HandleCall(){
    String Number = server.arg("number");String Nmae = server.arg("name");
    lcdReset();lcd.print("call: " + Nmae);lcd.setCursor(3,1);lcd.print(Number);
    server.send(200, "text/plain", "SmartClock::Phone Call Handler");
    Buzzer(300,10,true);delay(5000);}
void HandleSms(){
    String Number = server.arg("number");String Nmae = server.arg("name");
    lcdReset();lcd.print(Nmae);lcd.setCursor(0,1);lcd.print("SMS:" + Number);
    server.send(200, "text/plain", "SmartClock::Phone SMS Handler");
    Buzzer(500,5,true);delay(5000);}   
void HandleIpFinder(){
  server.send(302, "text/plain", WiFi.localIP().toString());} 

void ElegantOTAStart() {lcdReset();LCD_Print("Uploading..", 2,0,false);LCD_Print("ElegantOTA",3,1,false);}
void ElegantOTAEnd(bool success) {if (success) {lcdReset();LCD_Print("Upload Finished.", 0,0,false);LCD_Print("ElegantOTA",3,1,false);}}
void ArduinoOTAStart() {lcdReset();LCD_Print("Uploading..", 2,0,false);LCD_Print("ArdinoOTA",3,1,false);}
void ArduinoOTAEnd() {lcdReset();LCD_Print("Upload Finished.", 0,0,false);LCD_Print("ArdinoOTA",3,1,false);}