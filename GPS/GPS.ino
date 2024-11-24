#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps;

void setup() {
  setupGPS();
}

void loop() {
  showGPSInformation();
}
