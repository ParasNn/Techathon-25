#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>


const byte ledPin = 13; 
const byte switchPin = 3; 
const byte rxPin = 10;    // RX pin of HC-05
const byte txPin = 11;    // TX pin of HC-05
const byte statePin = 2;

// updated version

Servo myServo;  // Create a Servo object
int flipper = 180;

SoftwareSerial BTSerial(rxPin, txPin);  // Create a SoftwareSerial object for Bluetooth communication

const int debounceDelay = 50;  // Debounce delay in milliseconds
unsigned long lastDebounceTime = 0;
int lastButtonState = LOW;


void pairing(){
    Serial.println("Sending AT command....");

    //Send AT commands
    //int stateValue = digitalRead(statePin);
    //while(digitalRead(statePin) == LOW){
        BTSerial.write("AT\r\n");
        delay(500);
        Serial.println(BTSerial.readString());
        delay(500);
    //}
    

    // BTSerial.write("AT+STATE\r\n");
    // delay(500);
    // Serial.println(BTSerial.readString());
    // delay(500);
}

void setup() {
    myServo.attach(9);  // Attach the servo to pin D9
    //myServo.write(90);  // Start at neutral position
    delay(500); 

    pinMode(statePin, INPUT);
    pinMode(switchPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    BTSerial.begin(9600);
    Serial.begin(9600);
    //delay(500);
    //pairing();
    //Serial.println("End of AT command");
    BTSerial.listen();
}

String myWord = "";
bool lock = true;
void loop() {
    //digitalWrite(ledPin, HIGH); // Turn ON LED
    //delay(500);
    if((digitalRead(statePin) == HIGH)  && lock){
        digitalWrite(ledPin, HIGH);
        myServo.write(flipper); // Move to 180 degrees
        // Toggle between 180 and 0
        flipper = 0;
        lock = false;
    }else if((digitalRead(statePin) == LOW) && (!lock)){
        digitalWrite(ledPin, LOW);
        myServo.write(flipper); // Move to 0 degrees
        // Toggle between 180 and 0
        flipper = 180;
        lock = true;
    }
    //flipper = lock ? 180 : 0;
    //myServo.write(flipper); 

    // while(BTSerial.available()) {
    // // Bluetooth module is reading data and check for inmyWord
        
    //     myWord = BTSerial.readString();
    //     Serial.println(myWord);
    //     BTSerial.println("fuck you master");
    // }

   // int pinState = digitalRead(switchPin);

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


// if(myWord.equals("GO")){
//     digitalWrite(ledPin, HIGH); // Turn ON LED
//     delay(500);               // Wait for 1 second
    
//     myServo.write(flipper); // Move to 180 degrees
//     Serial.println("testing");
//     delay(1000);
//     // Toggle between 180 and 0
//     flipper = (flipper == 180) ? 0 : 180;
//     myWord = "";
// }else{
//     digitalWrite(ledPin, LOW);
// }
   
}