
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,/*reset=*/U8X8_PIN_NONE);
#define SOILHUMI A6
#include <SoftPWM.h>

SOFTPWM_DEFINE_CHANNEL(A3);

int Soilhumi = 0;
int Fan = 0;

void OLEDdraw(){
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_ncenB08_te);
  u8g2.drawStr(1,15,"SMART FAN");

  u8g2.drawStr(15,36,"Solihumi");
  u8g2.setCursor(85,36);
  u8g2.print(Soilhumi);
  u8g2.drawStr(114,36,"\xb0");
  u8g2.drawStr(119,36,"%");

  u8g2.drawStr(15,47,"Fan");
  u8g2.setCursor(85,47);
  u8g2.print(Fan);
  u8g2.drawStr(116,47,"%");

  u8g2.sendBuffer();
}

void setup(){
  u8g2.begin();
  SoftPWM.begin(490);
  pinMode(SOILHUMI, INPUT);
}

void loop(){
    Soilhumi = map(analogRead(SOILHUMI),0,1023,100,0);

    if (Soilhumi >= 30){
        Fan = 100;
        SoftPWM.set(Fan);
    }
    else if (Soilhumi <= 25){
        Fan = 0;
        SoftPWM.set(Fan);
    }
    else{
        Fan = 65;
        SoftPWM.set(Fan);
    }

    OLEDdraw();
 }
