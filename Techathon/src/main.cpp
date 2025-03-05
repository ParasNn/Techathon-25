#include <Arduino.h>
#include <SoftwareSerial.h>

//setup for IO pins -- BTSerial
const byte rxPin = 10;
const byte txPin = 11;
SoftwareSerial BTSerial(rxPin, txPin);

// put function declarations here:

void setup()
{
  //pin setup for bluetooth
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  BTSerial.begin(9600);
  Serial.begin(9600);

}

void loop()
{
  if (BTSerial.available()) {
    char c = BTSerial.read();
    Serial.write(c);
  }
  if (Serial.available()) {
    BTSerial.write("h");
  }
}