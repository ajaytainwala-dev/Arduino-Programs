#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 30
#define servoPin 9
#define fillSensPin 5

const int openTime = 6000;  // milliseconds

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo capServo;

void setup() {
  Serial.begin(115200);
  capServo.attach(servoPin);
  lcd.init();
  pinMode(fillSensPin, INPUT);
  capServo.write(28);  // Close cap initially
  displayText("SmartBin Bot", true, 1, 0);
  displayText("By Ajay", true, 1, 1);
  delay(500);
}

void loop() {
  delay(100);
  capObjectSensing();
}

int capObjectSensing() {
  distance = sonar.ping_cm();
  Serial.print("\n Distance is : ");
  Serial.print(distance);
  Serial.print("cm");
  if (distance <= 30 && distance > 8) {
    openCap();
  } else {
    capServo.write(28);  // Close cap
  }
  return distance;  // Added to return distance for potential use
}

void openCap() {
  for (int i = 28; i <= 105; i++) {
    displayText("Cap Opening", true, 1, 0);
    capServo.write(i);
    delay(10);
  }
  delay(openTime);  // Keep cap open for 5 seconds
  for (int i = 105; i >= 28; i--) {
    displayText("Cap Closing", true, 1, 0);
    capServo.write(i);
    delay(20);
  }
  fillLevel();  // Call fillLevel after cap closes
}

void fillLevel() {
  digitalWrite(fillSensPin, HIGH);
  duration = pulseIn(fillSensPin, HIGH);
  fillDistance = (duration / 10) / 10;
  Serial.println("\n Fill Distance : ");
  Serial.println(fillDistance);
  Serial.println(" CM ");

  if (fillDistance == 0) {
    lcd.clear();
    displayText("Dustbin is Full!", true, 0, 0);
    Serial.print("Dustbin is Full!");
  } else if (fillDistance >= 18.75) {
    lcd.clear();
    displayText("75% Full", true, 0, 0);
    Serial.print("Dustbin got filled 75% ");
  } else if (fillDistance >= 12.5) {
    lcd.clear();
    displayText("50% Full", true, 0, 0);
    Serial.print("Dustbin got filled 50% ");
  } else if (fillDistance >= 6.25) {
    lcd.clear();
    displayText("25% Full", true, 0, 0);
    Serial.print("Dustbin got filled 25% ");
  } else if (fillDistance == 25) {
    lcd.clear();
    displayText("Empty!", true, 0, 0);
    Serial.print("Dustbin is Empty! ");
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
