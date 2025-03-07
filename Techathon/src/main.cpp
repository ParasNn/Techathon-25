#include <Arduino.h>
#include <SoftwareSerial.h>

// Setup for IO pins -- BTSerial
const byte rxPin = 10;  // RX pin of HC-05
const byte txPin = 11;  // TX pin of HC-05
const int ledPin = 13;

SoftwareSerial BTSerial(rxPin, txPin);  // Create a SoftwareSerial object for Bluetooth communication

void setup()
{
  // Pin setup for IO
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Begin Bluetooth serial communication at 9600 baud rate
  BTSerial.begin(9600);
  // Begin the regular serial communication at 9600 baud rate (for debugging)
  Serial.begin(9600);
}

void loop()
{
  // Check if data is available from the Bluetooth device
  if (BTSerial.available()) {
    // Read the data from Bluetooth and send it to the Serial Monitor
    int c = BTSerial.read();
    //turn on LED based on phone input
    if (c == 1) {
      digitalWrite(ledPin, 1);
      Serial.println("led on\n");
    }
    else if (c == 0) {
      digitalWrite(ledPin, 0);
      Serial.println("led off\n");
    }
  }

  // Check if data is available from the Serial Monitor
  if (Serial.available()) {
    // Read the data from the Serial Monitor and send it to the Bluetooth device
    char c = Serial.read();  // Read the character from the Serial Monitor
    BTSerial.print(c);  // Send the character to the Bluetooth device
  }
}
