#define LAMP 17
uint32_t TimeCompare;
uint32_t StartTime = 0;

uint32_t TimeSum;
int Hour = 0;
float Minute = 1;

void setup(){
  pinMode(LAMP, OUTPUT);
  TimeSum = (uint32_t)(Hour*60+Minute)*60*1000;
  //TimeSum = 3000; 하면 3초마다 불 켜짐. 
  StartTime = millis();
}

void loop(){
  TimeCompare = (millis() - StartTime)/TimeSum;

  if (TimeCompare % 2 == 0){
    //3초마다 할 경우에는 0~2999까지는 3000으로 나눠도 몫이 0이니까 꺼진 상태
    digitalWrite(LAMP, LOW);
  }
  else if (TimeCompare % 2 == 1){
    digitalWrite(LAMP, HIGH);
  }
}
