//The code is written in Arduino IDE
//The code is free to use

/*This project detectes the motion through IR sensor and if its detected then the LED get on and Piezo Beeps and the LCD screen displays "Motion Detected"*/
//The Code is written by Ajay Tainwala
//For more information visit: www.circuitdigest.com


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address (use the correct address for your module)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the address if needed

void setup()
{
    //The LCD is connected to SDA and SCL pin of arduino

    Serial.begin(9600);
    lcd.init();      // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    pinMode(8, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(6, INPUT);
}
void loop()
{
    int sensValue = digitalRead(6);
    if (sensValue == LOW)
    {
        Serial.print("Motion Detected!");
        digitalWrite(8, HIGH);
        digitalWrite(13, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Motion Detected!");
        delay(1000);
    }
    else
    {
        digitalWrite(8, LOW);
        digitalWrite(13, LOW);
        lcd.setCursor(0, 0);
        lcd.clear();
    }
}
