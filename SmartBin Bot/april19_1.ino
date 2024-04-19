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
bool switchPressed = false;
const int openTime = 6000;  // milliseconds
// Container dimensions (adjust as needed)
const int container_height_cm = 23;

// Define fill level percentages
const int fill_levels[] = {0, 25, 50, 75, 100};  // Empty, 25%, 50%, 75%, Full

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
  pinMode(switchPin,LOW);
  capServo.write(28);  // Close cap initially
 defaultText();
  delay(500);



 

  if (!player.begin(playerSerial)) {
    Serial.println("DF player not connected");
    delay(500);
  } else {
    Serial.println("Df player connected");
    delay(500);
    player.volume(30);
  
  }
}

void loop() {

  // switchPressed = digitalRead(switchPin);
  delay(100);
  capObjectSensing();
  if (bluetooth.available() > 0) {
    char command = bluetooth.read();
    if (command == 'O' || command == 'o') {
      openLid();
    } else if (command == 'C' || command == 'c') {
      closeLid();
    }
  }

  // Switch control
  if (switchPressed == HIGH) {
    openLid();
   delay(15000);
    closeLid();
  } 
}

int capObjectSensing() {
  int distance = sonar.ping_cm();
  Serial.print("\n Distance is : ");
  Serial.print(distance);
  Serial.print("cm");
  if (distance <= 30 && distance > 8) {
    openLid();
    delay(6000);
    closeLid();
  } else {
      // Close cap
  }
  return distance;  // Added to return distance for potential use
}


void openLid() {

    playSound(1);
  for (int i = 28; i <= 105; i++) {
    capServo.write(i);
    delay(10);
  }
    displayText("Cap Opening", true, 3, 0);
    delay(1000);
    displayText("Cap is Open !!", true, 2, 0);


  // delay(openTime);  // Keep cap open for 5 seconds
}
void closeLid() {
    displayText("Cap Closing!", true, 2, 0);
  
    playSound(2);
  for (int i = 105; i >= 28; i--) {
    capServo.write(i);

    delay(20);
  }

  fillLevel();  // Call fillLevel after cap closes
}

void fillLevel() {
  digitalWrite(fillSensPin, HIGH);
  int duration = pulseIn(fillSensPin, HIGH);
 int  fillDistance = (duration / 10) / 10;
  Serial.println("\n Fill Distance : ");
  Serial.println(fillDistance);
  Serial.println(" CM ");

//   // Calculate fill level percentage
//   int fill_pct = int(100.0 * (1 - (fillDistance / (container_height_cm * 10))));  // Convert cm to mm

//   // Determine fill level index by finding closest level in the array
//   int level_index = 0;
//   for (int i = 1; i < sizeof(fill_levels) / sizeof(fill_levels[0]); i++) {
//     if (abs(fill_pct - fill_levels[i]) < abs(fill_pct - fill_levels[level_index])) {
//       level_index = i;
//     }
//   }

// Serial.print("Fill Level: ");
//   Serial.print(fill_levels[level_index]);
//   Serial.print("%, Distance (mm): ");
//   Serial.println(fillDistance);

  // displayText("Fill Level: ",true,0,0);
  // displayText(fill_levels[level_index],true,0,0);
   if (fillDistance == 0) {
     playSound(3);
      displayText("Dustbin is Full!", true, 0, 0);
      Serial.print("Dustbin is Full!");

    } else if (fillDistance >= 17.25 && fillDistance <19) {
       playSound(4);
      displayText("25% Full", false, 0, 0);
      delay(3000);
      defaultText();
      Serial.print("Dustbin got filled 25% ");
    } else if (fillDistance >= 11.5 || fillDistance <13) {
       playSound(5);
      displayText("50% Full", true, 0, 0);
      Serial.print("Dustbin got filled 50% ");
    } else if (fillDistance >= 5.75 && fillDistance <8) {
       playSound(6);
      displayText("75% Full", true, 0, 0);
      Serial.print("Dustbin got filled 75% ");

    } else if (fillDistance == 23 || fillDistance == 24 || fillDistance == 25) {
      playSound(3);
      displayText("Empty!", true, 0, 0);
      Serial.print("Dustbin is Empty! ");
    }
}

void displayText(String  data, bool backLight, int cursor, int line) {
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
   player.play(fileName);
}


int playSound(int fileName, int folderName) {
   player.playFolder(fileName, folderName);
}

void defaultText(){
  // displayText("SmartBin Bot", true, 0, 0);
  // displayText("By Ajay", true, 1, 1);

lcd.clear();
    lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SmartBin Bot");
  lcd.setCursor(1,1);
  lcd.print("By Ajay");
  
}
