/*
  SD card test for stm32 and SdFat library
    SD card attached to the primary SPI as follows:
        MISO  = PB14;
        MOSI  = PB15;
        SCK   = PB13;
        SS    = PB12;
*/
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

// #define SD_CS_PIN       PB12
// static SPIClass LandG_SPI(PB14, PB15, PB13, SD_CS_PIN);
// #define SD_CONFIG SdSpiConfig (SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ (18), &LandG_SPI)

File myFile;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // LandG_SPI.begin();
  Serial.println("Initializing SD card...");
  delay(100);
  // if (!SD.begin(SD_CONFIG)) {
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");

  if (SD.exists("TEST.TXT")) {
    Serial.println("TEST.TXT already exists.");
  } else {
    Serial.println("TEST.TXT does not exist, creating a new one.");
  }

  myFile = SD.open("TEST.TXT", FILE_WRITE);
  if (myFile) {
    Serial.println("Writing to TEST.TXT...");
    myFile.println("testing 1, 2, 3.");
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening TEST.TXT");
  }

  myFile = SD.open("TEST.TXT", O_RDONLY);
  if (myFile) {
    Serial.println("Read TEST.TXT:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error opening TEST.TXT");
  }

  if (SD.exists("TEST.TXT")) {
    Serial.println("TEST.TXT exists.");
  } else {
    Serial.println("TEST.TXT does not exist.");
  }
}

void loop() {
    if (Serial.available() > 0) {
        String inputString = Serial.readStringUntil('\n');
        myFile = SD.open("TEST.TXT", FILE_WRITE);
        if (myFile) {
            myFile.println(inputString);
            myFile.close();
            Serial.println("Write successful.");
        } else {
            Serial.println("Error opening TEST.TXT for writing.");
        }
    }
}