#include <SoftPWM.h>

SOFTPWM_DEFINE_CHANNEL(A3);

void setup() {
  // put your setup code here, to run once:
  SoftPWM.begin(490);

}

void loop() {
    for(int i=65;i<100;i++){
        SoftPWM.set(i);
        delay(100);
    }
    
    for(int i=100;i>65;i--){
        SoftPWM.set(i);
        delay(100);
    }
  // put your main code here, to run repeatedly:
//set(100) -> 가장 센 세기 2초 간격으로 반복

}
