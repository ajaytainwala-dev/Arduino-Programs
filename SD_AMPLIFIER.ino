#include <SD.h>
#include <TMRpcm.h>

const int SD_CS_PIN = 4;  // CS pin for the SD card module
const int speakerPin = 9; // Connect this pin to the PAM8403 amplifier input

TMRpcm tmrpcm;

void setup() {
  Serial.begin(9600);

  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD Card initialization failed!");
    return;
  }

  Serial.println("SD Card initialized.");

  // Set the speaker pin
  tmrpcm.speakerPin = speakerPin;

  // Set volume (0 to 7). Adjust as needed.
  tmrpcm.setVolume(5);

  // Play the audio file (replace "yourfile.wav" with the actual filename)
  tmrpcm.play("yourfile.wav");
}

void loop() {
  // Your main loop code here
}
