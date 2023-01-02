/*

  From:

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardAndMouseControl
*/

#include "Keyboard.h"
#include "Mouse.h"



// set pin numbers for switches:
//
const int aButton = 4;
const int bButton = 5;
const int cButton = 6;
const int dButton = 7;
const int eButton = 8;
const int twiddleSwitch = 11;

void setup() {
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(cButton, INPUT_PULLUP);
  pinMode(dButton, INPUT_PULLUP);
  pinMode(eButton, INPUT_PULLUP);
  
  pinMode(twiddleSwitch, INPUT_PULLUP);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
}

int ledinc = 0;
int led = LOW;
int twiddler = 0;
int dir = 0;

void loop() {
  
  delay(100);

  // blink the LED
  if (++ledinc > 10) {
    if (led == LOW) {
      led = HIGH;
    }
    else {
      led = LOW;
    }
    ledinc = 0;
    digitalWrite(LED_BUILTIN, led);
  }

  // twiddle the mouse a pixel every minute if enabled
  //
  if (digitalRead(twiddleSwitch) && (++twiddler > 600)) {
    twiddler = 0;
    switch (dir) {
      case 0:
        // move mouse up
        Mouse.move(0, -1);
        break;
      case 1:
        // move mouse down
        Mouse.move(0, 1);
        break;
      case 2:
        // move mouse left
        Mouse.move(-1, 0);
        break;
      case 3:
        // move mouse right
        Mouse.move(1, 0);
        break;
    }
    dir = 3 & ++dir;
  }
  
  // use serial input to control the mouse:
  if (Serial.available() > 0) {

  }

  // use the pushbuttons to control the keyboard:
  if (digitalRead(aButton) == LOW) {
    Keyboard.print("git status\r");
      delay(500);
  }
  if (digitalRead(bButton) == LOW) {
    Keyboard.print("git add *");
      delay(500);
  }
  if (digitalRead(cButton) == LOW) {
    Keyboard.print("git commit -m \"\"\b");
      delay(500);
  }
  if (digitalRead(dButton) == LOW) {
    Keyboard.print("git push");
      delay(500);
  }
  if (digitalRead(eButton) == LOW) {
    Keyboard.print("git pull origin master");
      delay(500);
  }
}
