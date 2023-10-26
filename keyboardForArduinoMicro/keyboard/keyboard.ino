#include "Keyboard.h"
//#include "Mouse.h"

void setup() {
  Keyboard.begin();
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, INPUT_PULLUP); //left
  pinMode(16, INPUT_PULLUP); //bottom
  pinMode(14, INPUT_PULLUP); //right
  pinMode(15, INPUT_PULLUP); //up
  pinMode(9, INPUT_PULLUP);  //space
  pinMode(8, INPUT_PULLUP);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  if (!digitalRead(8)) {
    delay(100);
    Keyboard.press(10); // Enter Key
    delay(1000);
    Keyboard.print("9900");
    Keyboard.releaseAll();
  }
}

void loop() {
  if (!digitalRead(2)) {
    while (!digitalRead(2)) {
      digitalWrite(4, 1);
    }
    digitalWrite(4, 0);
    delay(100);
    digitalWrite(5, 1);
    delay(50);
    digitalWrite(5, 0);
    delay(50);
    digitalWrite(5, 1);
    delay(50);
    digitalWrite(5, 0);
    Keyboard.press(KEY_LEFT_GUI);  // Press the Windows key
    delay(100);  // Delay for stability
    Keyboard.press(KEY_LEFT_SHIFT);  // Press the Shift key
    delay(100);  // Delay for stability
    Keyboard.press('s');  // Press the 's' key
    delay(100);  // Delay for stability
    Keyboard.releaseAll();  // Release all keys
    delay(10);
  } else if (!digitalRead(3)) {
    while (!digitalRead(3)) {
      delay(10);
      digitalWrite(4, 1);
    }
    digitalWrite(4, 0);
    delay(100);
    digitalWrite(5, 1);
    delay(100);
    digitalWrite(5, 0);
    delay(100);
    digitalWrite(5, 1);
    delay(100);
    digitalWrite(5, 0);
    Keyboard.print("080808");
    delay(100);
  } else if (!digitalRead(9)) {
    while (!digitalRead(9)) {
      delay(10);
    }
    Keyboard.press(32); // Space Key
    delay(10);
    Keyboard.releaseAll();
  } else if (!digitalRead(10)) {
    while (!digitalRead(10)) {
      delay(10);
    }
    Keyboard.press(KEY_LEFT_ARROW);
    delay(10);
    Keyboard.releaseAll();
  } else if (!digitalRead(16)) {
    while (!digitalRead(16)) {
      delay(10);
    }
    Keyboard.press(KEY_DOWN_ARROW);
    delay(10);
    Keyboard.releaseAll();
  } else if (!digitalRead(14)) {
    while (!digitalRead(14)) {
      delay(10);
    }
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(10);
    Keyboard.releaseAll();
  } else if (!digitalRead(15)) {
    while (!digitalRead(15)) {
      delay(10);
    }
    Keyboard.press(KEY_UP_ARROW);
    delay(10);
    Keyboard.releaseAll();
  }
  delay(10);
}
