/*

  From:

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardAndMouseControl
*/

#include "Keyboard.h"
#include "Mouse.h"



// set pin numbers for switches:
//
const int aButton = 4;
const int bButton = 9;
const int cButton = 6;
const int dButton = 7;
const int eButton = 8;
const int fButton = 12;
const int twiddleSwitch = 11;


void setup() {
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(cButton, INPUT_PULLUP);
  pinMode(dButton, INPUT_PULLUP);
  pinMode(eButton, INPUT_PULLUP);
  pinMode(fButton, INPUT_PULLUP);
  
  pinMode(twiddleSwitch, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
  delay(1000);
  Serial.write("Begin\n");
}

int ledinc = 0;
int led = LOW;
int twiddler = 0;
int dir = 0;

void loop() {
  
  delay(100);

  // blink the LED
  if (++ledinc > 6) {
    if (led == LOW) {
      led = HIGH;
    }
    else {
      led = LOW;
    }
    if (digitalRead(twiddleSwitch)) {
      ledinc = 4;
    }
    else {
      ledinc = 0;
    }
    
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
        Serial.write("up\n");
        break;
      case 1:
        // move mouse right
        Mouse.move(1, 0);
        Serial.write("right\n");
        break;
      case 2:
        // move mouse down
        Mouse.move(0, 1);
        Serial.write("down\n");
        break;
      case 3:
        // move mouse left
        Mouse.move(-1, 0);
        Serial.write("left\n");
        break;
    }
    dir = 3 & ++dir;
  }

  if (digitalRead(aButton) == LOW) {
    // Serial.write("aButton\n");
    Keyboard.println("git status");
    delay(100);
  }
  if (digitalRead(bButton) == LOW) {
    // Serial.write("bButton\n");
    Keyboard.print("git add !@#$%^&*() ABCDEFGH");
    Keyboard.write(42);
    Keyboard.write(KEY_RETURN);
 #if 0
    Keyboard.print("git add ");
    delay(100);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("*");
    delay(100);    
    Keyboard.releaseAll();
    delay(100);
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.releaseAll();
 #endif
    delay(100);
  }
  if (digitalRead(cButton) == LOW) {
    // Serial.write("cButton\n");
    Keyboard.print("git commit -m ");
    delay(100);
    Keyboard.press(KEY_LEFT_SHIFT);
        delay(100);
    Keyboard.print("\"");
    Keyboard.releaseAll();
    Keyboard.press(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("\"");
    Keyboard.releaseAll();
    delay(100);
  }
  if (digitalRead(dButton) == LOW) {
    // Serial.write("dButton\n");
    Keyboard.print("git push");
    delay(100);
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.releaseAll();
    delay(200);
  }
  if (digitalRead(eButton) == LOW) {
    // Serial.write("eButton\n");
        Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("$('#");
    delay(100);
    Keyboard.releaseAll();
    delay(300);
  }
   if (digitalRead(fButton) == LOW) {
    Keyboard.print("git pull origin master");
  //  Serial.write("fButton\n");
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.releaseAll();
    delay(400);
  }
}
