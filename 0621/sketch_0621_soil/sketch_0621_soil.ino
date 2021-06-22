#define SOILHUMI A6

int Soilhumi = 0;

void setup(){
    Serial.begin(9600);
    pinMode(SOILHUMI, INPUT);
}

void loop(){
    Soilhumi = map(analogRead(SOILHUMI),0,1023,100,0);

    Serial.print("현재 토양 습도:");
    Serial.println(Soilhumi);
    delay(500);
}
