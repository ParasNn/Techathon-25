#include <Arduino.h>

// put function declarations here:

void setup() {
  pinMode(9, OUTPUT); // Set pin 9 as an output
}

void loop() {
  for (int brightness = 0; brightness <= 255; brightness++) { 
    analogWrite(9, brightness); // Set LED brightness (0-255)
    delay(10); // Small delay for smooth transition
  }
  for (int brightness = 255; brightness >= 0; brightness--) { 
    analogWrite(9, brightness); // Dim the LED down
    delay(10);
  }
}