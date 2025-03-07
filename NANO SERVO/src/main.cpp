#include <Arduino.h>
#include <Servo.h>

Servo myServo;  // Create a Servo object
int flipper = 180;
void setup() {
    myServo.attach(9);  // Attach the servo to pin D9
    //myServo.write(90);  // Start at neutral position
    //delay(500); 
}

void loop() {
    myServo.write(flipper); // Move to 180 degrees
    delay(1000);        // Wait 1 second

    // Toggle between 180 and 0
    flipper = (flipper == 180) ? 0 : 180;
}