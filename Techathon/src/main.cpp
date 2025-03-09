#include <Arduino.h>
#include <SoftwareSerial.h>
#include <String.h>


// Setup for IO pins -- BTSerial
const byte rxPin = 10;    // RX pin of HC-05
const byte txPin = 11;    // TX pin of HC-05
const byte ledPin = 13;   // Board LED
const byte buzzerPin = 7; // buzzer

String inWord = "";
String Password = "Pass";
String command = "";
bool passAccept = false;
int commPtr = 0;

SoftwareSerial BTSerial(rxPin, txPin);  // Create a SoftwareSerial object for Bluetooth communication

struct Node {
  String data;  // Holds the String data
  Node* next;   // Points to the next node in the list
};

class LinkedList {
  public:
    Node* head;  // The first node in the list
    int size; 

    LinkedList() {
      head = nullptr;  // Initialize an empty list
      size = 0;
    }
  
    // Add a new node with a string at the end of the list
    void add(String token) {
      Node* newNode = new Node;  // Create a new node
      newNode->data = token;
      newNode->next = nullptr;
  
      if (head == nullptr) {
        head = newNode;  // If the list is empty, make the new node the head
      } else {
        Node* current = head;
        while (current->next != nullptr) {
          current = current->next;  // Traverse to the last node
        }
        current->next = newNode;  // Append the new node
      }
      size++;
    }

    void clear() {
      Node* current = head;
      Node* nextNode;
  
      while (current != nullptr) {
        nextNode = current->next;
        delete current;  // Delete the current node
        current = nextNode;
      }
      head = nullptr;  // Reset head to nullptr (empty list)
      size = 0;
    }

    String get(int index) {
      if (index >= 0 && index < size) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
          current = current->next;  // Move to the next node
        }
        return current->data;  // Return the data of the node at the specified index
      } else {
        return "";  // Return an empty string if the index is out of bounds
      }
    }
  
    // Get the size of the list
    int getSize() {
      return size;
    }
  };
  
LinkedList commands;


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
  if (BTSerial.available()) {
    command = BTSerial.readString();
    Serial.println("Received: " + command);
    BTSerial.flush();
  }

  command.trim();
  int index;

  while ((index = command.indexOf(' ')) != -1) {
    // Extract the word before the space
    String word = command.substring(0, index);
    
    // Only add the word if it's not empty
    if (word.length() > 0) {
      commands.add(word);
    }
    // Remove the processed part + space
    command = command.substring(index + 1);
    command.trim();  // Trim again to remove leading spaces
  }

  if (command.length() > 0) {
    commands.add(command);  // Add the last word (if any)
  }

  for (int i = 0; i < commands.getSize(); i++) {
    String token = commands.get(i);
    wordChecker(token);
  }

  if(commands.getSize() != 0){
    commands.clear();
  }
  command = "";
}
