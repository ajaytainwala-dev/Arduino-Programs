// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------
// { All Headers
#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//}


// { All Preposesor
#define TRIGGER_PIN 12    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 11       // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define servoPin 9
bool fillSens = true;
int distPin = 5;
unsigned long duration;
uint16_t fillDistance = 0;
static int distance;
// }

// { All Objects
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo capServo;
// }

void setup() {
  // { All Inits
  Serial.begin(115200);  // Open serial monitor at 115200 baud to see ping results.
  capServo.attach(servoPin);
  lcd.init();  // initialize the lcd
  // }
  // lcd.backlight();
  // { All Initialization and declaration
  pinMode(distPin, INPUT); 
  capServo.write(28);
  lcd.setCursor(3, 0);
  //  }

  lcd.print("SmartBin BOT");
  lcd.setCursor(3, 1);
  lcd.print("By Ajay");

  delay(500);
}

void loop() {
  delay(100);
  capObjectSensing();
}

int capObjectSensing() {
  distance = sonar.ping_cm();  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("\n Distance is : ");
  Serial.print(distance);
  Serial.print("cm");
  if (distance <= 30 && distance > 8) {
    fillSens = false;
    for (int i = 28; i <= 105; i++) {
      capServo.write(i);
      delay(10);
      Serial.print(fillSens);
    }
    delay(5000);
    for (int i = 105; i >= 28; i--) {
      capServo.write(i);
      delay(20);
    }
  } else {
    capServo.write(28);
    fillSens = true;
  }
  fillLevel();
}

int fillLevel() {
  if (fillSens == false) {
    digitalWrite(6, HIGH);
    duration = pulseIn(distPin, HIGH);
    fillDistance = (duration / 10) / 10;
    Serial.println("\n Fill Distance : ");
    Serial.println(fillDistance);
    Serial.println(" CM ");

    if (fillDistance == 0) {
      Serial.print("Dustbin is Full!");  // full
      displayText("Dustbin is Full!",true,3,0);
    } else if (fillDistance >= 18.75) {
      Serial.print("Dustbin got filled 75% ");  //75%
    } else if (fillDistance >= 12.5) {
      Serial.print("Dustbin got filled 50% ");  //50%
    } else if (fillDistance >= 6.25) {
      Serial.print("Dustbin got filled 25% ");  //25%
    } else if (fillDistance == 25) {
      Serial.print("Dustbin is Empty! ");  //Empty
    }

  } else {
    digitalWrite(6, LOW);
  }
}

void displayText(char data[], bool backLight, int cursor, int line) {
  if (backLight) {
    lcd.backlight();
  } else {
    //none
  }
  lcd.setCursor(cursor, line);
  lcd.print(data);
}
