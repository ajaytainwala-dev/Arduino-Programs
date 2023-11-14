#include <AFMotor.h>



const int trigPin = A0;

const int echoPin  = A2;

long duration;

int distance;



AF_DCMotor motor1(1, MOTOR12_1KHZ);

AF_DCMotor  motor2(2, MOTOR12_1KHZ);

AF_DCMotor motor3(3, MOTOR12_1KHZ);

AF_DCMotor motor4(4,  MOTOR12_1KHZ);



 



void setup() {

  pinMode(trigPin, OUTPUT); 

  pinMode(echoPin, INPUT);



  Serial.begin(9600);

  

  motor1.setSpeed(250);

  motor2.setSpeed(250);

  motor3.setSpeed(250);

  motor4.setSpeed(250);

  

}



void loop() 

{

  

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin,  HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin,  HIGH);

distance= duration*0.034/2;

Serial.print("Distance: ");

Serial.println(distance);



movestop();

delay(1000);



if(distance  < 75)

{   

 

 backward();

    delay(1000);

  

     

    movestop();

    delay(1000);

    

    lookright();

    delay(750);

}

else

{

  forward();

  delay(1000); 



}





}





void movestop()

{

  motor1.run(RELEASE);

  motor2.run(RELEASE);

  motor3.run(RELEASE);

  motor4.run(RELEASE);

}



void  forward()

{

  motor1.run(FORWARD);

  motor2.run(FORWARD);

  motor3.run(FORWARD);

  motor4.run(FORWARD);

  motor1.setSpeed(200);

  motor2.setSpeed(200);

  motor3.setSpeed(200);

  motor4.setSpeed(200);

 

}



void backward()

{

  motor1.run(BACKWARD);

  motor2.run(BACKWARD);

  motor3.run(BACKWARD);

  motor4.run(BACKWARD);

  motor1.setSpeed(200);

  motor2.setSpeed(200);

  motor3.setSpeed(200);

  motor4.setSpeed(200);

 

}

    

void  lookright()

{

  motor1.run(FORWARD);

  motor2.run(FORWARD);

  motor3.run(BACKWARD);

  motor4.run(BACKWARD);

  motor1.setSpeed(200);

  motor2.setSpeed(200);

  motor3.setSpeed(200);

  motor4.setSpeed(200);

 

}



void lookleft()

{

  motor1.run(BACKWARD);

  motor2.run(BACKWARD);

  motor3.run(FORWARD);

  motor4.run(FORWARD);

  motor1.setSpeed(200);

  motor2.setSpeed(200);

  motor3.setSpeed(200);

  motor4.setSpeed(200);

 

}

