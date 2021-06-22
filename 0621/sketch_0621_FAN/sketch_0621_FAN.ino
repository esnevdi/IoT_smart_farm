#include <SoftPWM.h>

SOFTPWM_DEFINE_CHANNEL(A3);

void setup() {
  // put your setup code here, to run once:
  SoftPWM.begin(490);

}

void loop() {
    SoftPWM.set(100);
    delay(2000);
    SoftPWM.set(0);
    delay(2000);
  // put your main code here, to run repeatedly:
  //set(100) -> 가장 센 세기 2초 간격으로 반복

}
