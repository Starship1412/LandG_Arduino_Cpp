#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8); // CE, CSN
//address through which two modules communicate.
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);//Transmitter RF Power Setting
  //MIN=-18dBm, LOW=-12dBm, HIGH=-6dBm, MAX=0dBm.
  radio.setChannel(108); //above most WiFi frequencies. RF Channel setting 0-125
  radio.setDataRate( RF24_250KBPS ) ;
  //set the address
  radio.openWritingPipe(address);
  //Set module as transmitter
  radio.stopListening();
}

void loop() {
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to an angle (0 - 180°):
  int servoPos = (int)sensorValue * (180.0 / 1023.0);
  //Send message to receiver
  String stext = String(servoPos);
  char text[32];
  stext.toCharArray(text, 32);
  radio.write(&text, sizeof(text));
  delay(100);
}