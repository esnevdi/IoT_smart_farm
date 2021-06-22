#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,/*reset=*/U8X8_PIN_NONE);
#define SOILHUMI A6
#define PUMP 16

int Soilhumi = 0;
int Pump = 0;

void OLEDdraw(){
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_ncenB08_te);
  u8g2.drawStr(1,15,"SMART FARM");

  u8g2.drawStr(15,36,"Soilhumi");
  u8g2.setCursor(85,36);
  u8g2.print(Soilhumi);
  u8g2.drawStr(116,36,"%");  

  u8g2.drawStr(15,47,"Pump");
  u8g2.setCursor(85,47);
  u8g2.print(Pump);
  u8g2.drawStr(116,47,"%"); 

  u8g2.sendBuffer();
}

void setup(){
  u8g2.begin();
  pinMode(PUMP, OUTPUT);  
}

void loop(){
  Soilhumi = map(analogRead(SOILHUMI),0,1023,100,0);
  if (Soilhumi<=30){
    digitalWrite(PUMP, HIGH);
  }
  else if (Soilhumi>=60){
    digitalWrite(PUMP, LOW);
  }
  OLEDdraw();
}
