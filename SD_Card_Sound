#include <SD.h>
#include <TMRpcm.h>

#define SD_CS_PIN 4 // Chip select pin for the SD card module
#define SPEAKER_PIN 9 // Pin connected to the speaker (PWM capable)

TMRpcm audio;

void setup() {
  audio.speakerPin = SPEAKER_PIN;
  Serial.begin(9600);

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed");
    return;
  }

  Serial.println("SD card initialized");
}

void loop() {
  // Play sound file "sound1.wav"
  audio.play("sound1.wav");

  // You can add more sound files to play here, e.g., audio.play("sound2.wav");

  while (audio.isPlaying()) {
    // Wait for the audio to finish playing
  }
}
