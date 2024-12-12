int ViewMode = 0;
void LCD_Print(String text,int cur,int curr,boolean fclear){if (fclear){lcd.clear();}lcd.setCursor(cur,curr);lcd.print(text);}
void lcdReset(){lcd.clear();lcd.home();}  
void GetIpAddr() {if (WiFi.isConnected()){LCD_Print(WiFi.SSID(),0,0,true);lcd.setCursor(0,1);lcd.print(WiFi.localIP());}else{LCD_Print(WiFi.softAPSSID(),0,0,true);lcd.setCursor(0,1);lcd.print(WiFi.softAPIP());}delay(10000);}
void softWareLoop(){
if (!digitalRead(D8)){Buzzer(100,0,0);while (!digitalRead(D8)){}Open_Menu();}
if (!digitalRead(D5)) {Buzzer(100,0,0);ViewMode = ViewMode+1;while (!digitalRead(D5)){};}
if (WiFi.isConnected()){lcd.setCursor(15, 1);lcd.print("C");}else if(WiFi.softAPgetStationNum() >= 1){lcd.setCursor(15, 1);lcd.print("A");}
if (!WiFi.isConnected()) {wifiMulti.run(5000);}MDNS.update();
lcd.setBacklight(BackLight);digitalWrite(LED_BUILTIN,BackLight);server.handleClient();timeClient.update();delay(50);ArduinoOTA.handle();ElegantOTA.loop();}
void Buzzer(int delayl,int repet,boolean last){
      for (int i = 0; i <= repet; i++){
      digitalWrite(BuzzerPin,1);delay(delayl);digitalWrite(BuzzerPin,0);
      if (last) {delay(delayl);}}}  
void Open_Menu() {
  lcdReset();int Item = 0;boolean inMenu = true;
  while (inMenu) {
    delay(200);
    if (!digitalRead(D5)) {Buzzer(100,0,0);switch (Item) {case 0:BackLight = !BackLight;inMenu = false;break;case 2:GetIpAddr();break;case 3:inMenu = false;break;}}
    if (!digitalRead(D8)) { Item = Item + 1; Buzzer(100,0,0);}
    switch (Item) {
      case 0: LCD_Print("Clock-Menu",4,0,true);LCD_Print(">> Toogle BackLed",0,1,false);break;
      case 1: LCD_Print(">> AutoBackLed",0,0,true);LCD_Print("> IpAdder",0,1,false);break;
      case 2: LCD_Print(">  AutoBackLed",0,0,true);LCD_Print(">> IpAdder",0,1,false);break;
      case 3: LCD_Print("> IpAdder",0,0,true);LCD_Print(">> Exit",0,1,false);break;
      default:Item = 0;break;}}}
void ShowClock(){delay(300);lcd.clear();
switch (ViewMode) {
    case 0:{int hour = timeClient.getHours() % 12;int Minute = timeClient.getMinutes();EBN.print(hour / 10, 0);EBN.print(hour % 10, 3);
    EBN.print(Minute / 10, 6);EBN.print(Minute % 10, 9);lcd.setCursor(13,1);lcd.print(timeClient.getSeconds());break;}
    case 1:{int hour = timeClient.getHours() % 12;int Minute = timeClient.getMinutes();EBN.print(hour / 10, 0);EBN.print(hour % 10, 3);
      time_t epochTime = timeClient.getEpochTime();struct tm *ptm = gmtime ((time_t *)&epochTime);
      int monthDay = ptm->tm_mday;int currentMonth = ptm->tm_mon+1;int currentYear = ptm->tm_year+1900;
      String currentMonthName = months[currentMonth-1];String weekDay = weekDays[timeClient.getDay()];String currentDate = String(monthDay)  + "/" + String(currentMonth);
      EBN.print(Minute / 10, 6);EBN.print(Minute % 10, 9);lcd.setCursor(13,1);lcd.print(timeClient.getSeconds());
      Date now(currentYear,currentMonth,monthDay );
      now.JDate();
      LCD_Print(String(now.JDay())+ String(now.JMonth()),13,0,false);
      break;}
      default:ViewMode = 0;break;}}

void Load(){
  lcd.init();lcd.setBacklight(BackLight);
  int L = 0;lcd.print("Loading..");
  while (L < 15) {
    switch (L) {
      case 0:LCD_Print("Set PinMode", 0,0,false);pinMode(D8, INPUT_PULLUP);pinMode(D5, INPUT_PULLUP);pinMode(BuzzerPin, OUTPUT);pinMode(LED_BUILTIN,OUTPUT);break;
      case 3:LCD_Print("Wifi Setup..", 0,0,false);server.on("/call", HandleCall);server.on("/sms", HandleSms);server.on("/ipaddr",HandleIpFinder);
        wifiMulti.addAP(ssid, password);wifiMulti.addAP(ssid0, password0);WiFi.softAP("SmartClock+", "12345678");wifiMulti.run(5000);
        WiFi.setHostname("SmartClockPlus");server.begin();ArduinoOTA.setHostname("SmartClockPlus");ArduinoOTA.setPassword("4884");
        ElegantOTA.onStart(ElegantOTAStart);ElegantOTA.onEnd(ElegantOTAEnd);ArduinoOTA.onStart(ArduinoOTAStart);ArduinoOTA.onEnd(ArduinoOTAEnd);
        ArduinoOTA.begin();ElegantOTA.begin(&server);MDNS.begin("smartclockplus");break;
      case 7:LCD_Print("Lib Init.....", 0,0,false);EBN.begin();timeClient.begin();Serial.begin(9600);break;
      case 10:LCD_Print("Loading.........", 0,0,false);break;
      case 12:Buzzer(150,3,1);break;}
    lcd.setCursor(L, 1);lcd.print("0");delay(200);L++;}}  