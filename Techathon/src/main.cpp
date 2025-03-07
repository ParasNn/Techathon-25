#include <Arduino.h>
#include <SoftwareSerial.h>
#include <String.h>

// Setup for IO pins -- BTSerial
const byte rxPin = 10;  // RX pin of HC-05
const byte txPin = 11;  // TX pin of HC-05
const int ledPin = 13;
String inWord = "";

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
  // Check if we have connection with the Bluetooth device
  if (BTSerial.available()) {
    // Bluetooth module is reading data and check for inWord
    char c = BTSerial.read();

    // Check for end of inWord (space or newline)
    if (c == ' ' || c == '\n' || c == '\r') {
      if (inWord.length() > 0) {
        Serial.print("Received inWord: ");
        Serial.println(inWord);
        inWord = ""; // Clear the inWord for the next one
      }
    }
    else {
      inWord += c; // Add character to the inWord
    }
  }

  // Check if data is available from the Serial Monitor
  if (Serial.available()) {
    // Read the data from the Serial Monitor and send it to the Bluetooth device
    char c = Serial.read();  // Read the character from the Serial Monitor
    BTSerial.print(c);  // Send the character to the Bluetooth device
  }
}
