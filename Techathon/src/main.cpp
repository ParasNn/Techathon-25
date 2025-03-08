#include <Arduino.h>
#include <SoftwareSerial.h>
#include <String.h>

// Setup for IO pins -- BTSerial
const byte rxPin = 10;    // RX pin of HC-05
const byte txPin = 11;    // TX pin of HC-05
const byte ledPin = 13;   // Board LED
const byte buzzerPin = 8; // buzzer

String inWord = "";
String Password = "Pass";
bool passAccept = false;

String commands[10];
int commPtr = 0;

SoftwareSerial BTSerial(rxPin, txPin);  // Create a SoftwareSerial object for Bluetooth communication

void passChecker(String wordIn)
{
  if (wordIn.equals(Password)) {
    passAccept = true;
    BTSerial.print("Main");
    return;
  }
  else {
    // enable buzzerfor x seconds
    for (int i = 0; i < 5; i++) {
      digitalWrite(buzzerPin, 1);
      delay(100);
      digitalWrite(buzzerPin, 0);
      delay(100);
      BTSerial.print("Wrong password");
    }
  }
}

bool lightTool(String wordIn, bool lightMode)
{
  if (lightMode) {
    if (wordIn.equals("ON")) {
      digitalWrite(ledPin, 1);
      BTSerial.print("Light On");
      return false;
    }
    else if (wordIn.equals("OFF")) {
      digitalWrite(ledPin, 0);
      BTSerial.print("Light Off");
      return false;
    }
    else {
      BTSerial.print("No command found");
      return true;
    }
  }
  else if (wordIn.equals("Light")) {
    BTSerial.print("Light mode");
    return true;
  }
  return false;
}

void wordChecker(String wordIn)
{
  static bool lightMode = false;

  if (passAccept) {
    if (wordIn.equals("Exit")) {
      passAccept = false;
      return;
    }
    lightMode = lightTool(wordIn, lightMode);
  }
  else {
    passChecker(wordIn);
  }

}

void setup()
{
  // Pin setup for IO
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

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

    if (c == '.') {
      for (int i = 0; i < commPtr; i++) {
        wordChecker(commands[i]);
      }
      Serial.print("Received Word: " + inWord + " \n");
      wordChecker(inWord);
      inWord = "";
      commPtr = 0;
    }
    else if (c == ' ' || c == '\n' || c == '\r') {
      if (inWord.length() > 0) {
        Serial.print("Received Word: " + inWord + " \n");
        commands[commPtr++] = inWord;
        inWord = ""; // Clear the inWord for the next one
      }
    }
    else {
      inWord += c; // Add character to the inWord
    }
  // Check for end of inWord (space or newline)

  }
}
