#include <Arduino.h>
#include <Servo.h>

const byte ledPin = 13; 
const byte switchPin = 3; 


Servo myServo;  // Create a Servo object
int flipper = 180;

const int debounceDelay = 50;  // Debounce delay in milliseconds
unsigned long lastDebounceTime = 0;
int lastButtonState = LOW;


void setup() {
    myServo.attach(9);  // Attach the servo to pin D9
    myServo.write(90);  // Start at neutral position
    delay(500); 
   
    pinMode(switchPin, INPUT);
    pinMode(ledPin, OUTPUT);

}

void loop() {

    int pinState = digitalRead(switchPin);


    // If the button state has changed, reset the debounce timer
    if (pinState != lastButtonState) {
        lastDebounceTime = millis();  // Set the timer to the current time
}

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

   
}