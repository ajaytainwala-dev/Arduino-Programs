#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>



#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 30
#define servoPin 10
#define fillSensPin 5
#define bluRX 2
#define bluTX 3
#define dfRX 8
#define dfTX 9
#define switchPin 4
bool switchPressed = false

const int openTime = 6000;  // milliseconds

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo capServo;
SoftwareSerial bluetooth(bluRX, bluTX);
SoftwareSerial playerSerial(dfRX, dfTX);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(115200);
  bluetooth.begin(38400);
  playerSerial.begin(9600);
  capServo.attach(servoPin);
  lcd.init();



  pinMode(fillSensPin, INPUT);
  pinMode(switchPin, INPUT);
  capServo.write(28);  // Close cap initially
  displayText("SmartBin Bot", true, 1, 0);
  displayText("By Ajay", true, 1, 1);
  delay(500);



  // Initialize DF Mini player
  while (!player.begin(DFPLAYER_PIN_CS, DFPLAYER_PIN_DCLK, DFPLAYER_PIN_DIN)) {
    Serial.println("Unable to connect to DFPlayer Mini...");
    delay(500);
  }
  Serial.println("DFPlayer Mini connected successfully.");
  dfplayer.volume(20);  // Set volume (adjust as needed)


  if (!player.begin(playerSerial)) {
    Serial.println("DF player not connected");
    delay(500);
  } else {
    Serial.println("Df player connected");
    delay(500);
    player.setVolume(30);
    player.
  }
}

void loop() {

  switchPressed = digitalRead(switchPin);
  delay(100);
  capObjectSensing();
  if (bluetooth.available() > 0) {
    char command = bluetooth.read();
    if (command == 'OPEN' || command == 'open') {
      openLid();
    } else if (command == 'CLOSE' || command == 'close') {
      closeLid();
    }
  }

  // Switch control
  if (switchPressed) {
    openLid();
  } else {
    closeLid();
  }
}

int capObjectSensing() {
  distance = sonar.ping_cm();
  Serial.print("\n Distance is : ");
  Serial.print(distance);
  Serial.print("cm");
  if (distance <= 30 && distance > 8) {
    openLid();
  } else {
    capServo.write(28);  // Close cap
  }
  return distance;  // Added to return distance for potential use
}


void openLid() {
  if (player.available())
    playSound(1);
  for (int i = 28; i <= 105; i++) {
    displayText("Cap Opening", true, 1, 0);
    capServo.write(i);
    delay(10);
  }

  delay(openTime);  // Keep cap open for 5 seconds
}
void closeLid() {
  if (player.available())
    playSound(2);
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

    displayText("Dustbin is Full!", true, 0, 0);
    Serial.print("Dustbin is Full!");
  } else if (fillDistance >= 18.75) {

    displayText("75% Full", true, 0, 0);
    Serial.print("Dustbin got filled 75% ");
  } else if (fillDistance >= 12.5) {

    displayText("50% Full", true, 0, 0);
    Serial.print("Dustbin got filled 50% ");
  } else if (fillDistance >= 6.25) {

    displayText("25% Full", true, 0, 0);
    Serial.print("Dustbin got filled 25% ");
  } else if (fillDistance == 25) {

    displayText("Empty!", true, 0, 0);
    Serial.print("Dustbin is Empty! ");
  }
}

void displayText(char data[], bool backLight, int cursor, int line) {
  lcd.clear();
  if (backLight) {
    lcd.backlight();
  } else {
    //none
  }
  lcd.setCursor(cursor, line);
  lcd.print(data);
}


int playSound(int fileName) {
  return player.play(fileName);
}


int playSound(int fileName, int folderName) {
  return player.playFolder(fileName, folderName);
}
