#include "DHT.h"
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,/*reset=*/U8X8_PIN_NONE);
#define SOILHUMI A6
#include <SoftPWM.h>
#define PUMP 16
#define DHTPIN A1
#define DHTTYPE DHT22
#define LAMP 17

DHT dht(DHTPIN, DHTTYPE);
uint32_t DataCaptureDelay_DHT = 2000;
uint32_t DataCaptureDelay_SOIL = 3000;
uint32_t DataCapture_ST = 0;
uint32_t DataCapture_DHT = 0;
uint32_t DataCapture_SOIL = 0;
uint32_t TimeSum = 3000;
uint32_t TimeCompare;

SOFTPWM_DEFINE_CHANNEL(A3);

int Soilhumi = 0;
int Fan = 0;
int Pump = 0;
float Temp;
float Humi;
int Lamp = 0;

void OLEDdraw(){
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_ncenB08_te);
  //u8g2.drawStr(1,15,"SMART FAN");

  u8g2.drawStr(1,15,"Temp");
  u8g2.setCursor(71,15);
  u8g2.print(Temp);
  u8g2.drawStr(100,15,"\xb0");
  u8g2.drawStr(105,15,"C");

  u8g2.drawStr(1,25,"Humidity");
  u8g2.setCursor(71,25);
  u8g2.print(Humi);
  u8g2.drawStr(100,25,"%");

  u8g2.drawStr(1,35,"Solihumi");
  u8g2.setCursor(71,35);
  u8g2.print(Soilhumi);
  u8g2.drawStr(100,35,"%");

  //u8g2.drawStr(1,45,"RUN:1");
  u8g2.setCursor(1,45);
  u8g2.print("RUN:1  ");
  u8g2.setCursor(71,45);
  u8g2.print(Fan);
  u8g2.print(" ");
  u8g2.print(Pump);
  u8g2.print(" ");
  u8g2.println(Lamp);
  
  u8g2.drawStr(1,55,"LED ON/OFF");
  u8g2.setCursor(90,55);
  u8g2.print(TimeSum/1000);
  u8g2.drawStr(100,55,"min");
  
  u8g2.sendBuffer();
}

void setup(){
  dht.begin();
  u8g2.begin();
  SoftPWM.begin(490);
  pinMode(SOILHUMI, INPUT);
  pinMode(PUMP, OUTPUT); 
  pinMode(LAMP, OUTPUT);
  DataCapture_ST = millis(); 
  DataCapture_DHT = millis();
  DataCapture_SOIL = millis();
}

void loop(){
  if ((millis()-DataCapture_DHT) > DataCaptureDelay_DHT){
    Humi = dht.readHumidity();
    Temp = dht.readTemperature();
    DataCapture_DHT = millis();
  }

  if ((millis()-DataCapture_SOIL) > DataCaptureDelay_SOIL){
    Soilhumi = map(analogRead(SOILHUMI),0,1023,100,0);
    DataCapture_SOIL = millis();
  }

  if (Soilhumi>=30 && Soilhumi<=60){
    digitalWrite(PUMP, HIGH);
    Pump = 1;
  }
  else{
    digitalWrite(PUMP, LOW);
    Pump = 0;
  }

  if (Temp >= 29){
      Fan = 1;
      SoftPWM.set(100);
  }
  else if (Soilhumi <= 20){
      Fan = 0;
      SoftPWM.set(0);
  }
  else{
      Fan = 1;
      SoftPWM.set(65);
  }

  TimeCompare = (millis() - DataCapture_ST)/TimeSum;

  if (TimeCompare % 2 == 0){
    digitalWrite(LAMP, LOW);
    Lamp = 0;
  }
  else if (TimeCompare % 2 == 1){
    digitalWrite(LAMP, HIGH);
    Lamp = 1;
  }

  OLEDdraw();
}
