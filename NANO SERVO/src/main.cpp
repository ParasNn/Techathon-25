#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>


const byte ledPin = 13; 
const byte switchPin = 3; 
const byte rxPin = 10;    // RX pin of HC-05
const byte txPin = 11;    // TX pin of HC-05


Servo myServo;  // Create a Servo object
int flipper = 180;

SoftwareSerial BTSerial(rxPin, txPin);  // Create a SoftwareSerial object for Bluetooth communication

const int debounceDelay = 50;  // Debounce delay in milliseconds
unsigned long lastDebounceTime = 0;
int lastButtonState = LOW;


void setup() {
    myServo.attach(9);  // Attach the servo to pin D9
    myServo.write(90);  // Start at neutral position
    delay(500); 
   
    pinMode(switchPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    BTSerial.begin(9600);
    Serial.begin(9600);
}

String myWord = "";
void loop() {


    while(BTSerial.available()) {
    // Bluetooth module is reading data and check for inmyWord
        Serial.print("test\n");
        myWord = BTSerial.readStringUntil(' ');
    }

    //int pinState = digitalRead(switchPin);

/*
    // If the button state has changed, reset the debounce timer
    if (pinState != lastButtonState) {
        lastDebounceTime = millis(); } // Set the timer to the current time
        */



/*
if ((millis() - lastDebounceTime) > debounceDelay) {
    if(pinState == HIGH){
        digitalWrite(ledPin, HIGH); 
        myServo.write(flipper); // Move to 180 degrees
        delay(1000);
        // Toggle between 180 and 0
        flipper = (flipper == 180) ? 0 : 180;
    } else{
        digitalWrite(ledPin, LOW);
    }
}
lastButtonState = pinState;
*/
if(myWord.equals("Go")){
    digitalWrite(ledPin, HIGH); 
    myServo.write(flipper); // Move to 180 degrees
    Serial.println("testing");
    delay(2000);
    // Toggle between 180 and 0
    flipper = (flipper == 180) ? 0 : 180;
    myWord = "";
}else{
    digitalWrite(ledPin, LOW);
}
   
}