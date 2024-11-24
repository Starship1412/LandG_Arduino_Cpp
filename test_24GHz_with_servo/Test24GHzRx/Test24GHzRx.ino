//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


Servo myservo;  // create servo object to control a servo

//create an RF24 object
RF24 radio(9, 8); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";


void setup()
{
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  
  while (!Serial);
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW); //Transmitter RF Power Setting
  //MIN=-18dBm, LOW=-12dBm, HIGH=-6dBm, MAX=0dBm.
  radio.setChannel(108); //above most WiFi frequencies. RF Channel setting 0-125
  radio.setDataRate( RF24_250KBPS ) ;
  //set the address
  radio.openReadingPipe(0, address);
  //Set module as receiver
  radio.startListening();
}


void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    String stext = text;
    int servoPos = stext.toInt();
    Serial.println(servoPos);
    myservo.write(servoPos);
  }
}
