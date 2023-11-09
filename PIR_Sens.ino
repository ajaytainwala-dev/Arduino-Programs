#include<Arduino.h>
int led= 13;
int sensor =2;
int state = LOW ;
int val=0;

void setup(){
    pinMode(led,OUTPUT);
    pinMode(sensor,INPUT);
    Serial.begin(9600);

}
 

void loop(){
    val = digitalRead(sensor);
    if (val == HIGH){
        digitalWrite(led,LOW);
        delay(100);

        if (state == HIGH){
            Serial.println("Motion Detected!");
            State = HIGH;

        }
    }else{
        digitalWrite(led,HIGH);
        delay(200);
        if (state== HIGH){
            Serial.println("Motion Stopped!!");
            state=LOW;
        }
    }
    delay(5000);
}