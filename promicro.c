#include <Joystick.h>
#include <ResponsiveAnalogRead.h>

Joystick_ Joystick;

ResponsiveAnalogRead analogOne(A0, true);
ResponsiveAnalogRead analogTwo(A1, true);
ResponsiveAnalogRead analogThree(A2, true);
ResponsiveAnalogRead analogFour(A3, true);

void setup() {
//  Serial.begin(9600);

  // Set Axis Range for Pots
  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
  Joystick.setRzAxisRange(0, 1023);
  Joystick.setZAxisRange(0, 1023);

  // Enable pins 0-9 for buttons
  for (int i=0; i<11; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  
  // Turn off LEDs on board
  pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);

  // Set joystick to send only when called.
  Joystick.begin(false);
}

byte allButtons[11];

void loop() {
  analogOne.update();
  analogTwo.update();
  analogThree.update();
  analogFour.update();
  
  Joystick.setRxAxis(analogOne.getValue());
  Joystick.setRyAxis(analogTwo.getValue());
  Joystick.setRzAxis(analogThree.getValue());
  Joystick.setZAxis(analogFour.getValue());

    for (int i=0; i<11; i++) {
      if (digitalRead(i)) {
        allButtons[i] = 0;
      } 
      else {
        allButtons[i] = 1;
      }
      Joystick.setButton(i, allButtons[i]);
    }

    for (int i=14; i<17; i++) {
      if (digitalRead(i)) {
        allButtons[i] = 0;
      } 
      else {
        allButtons[i] = 1;
      }
      Joystick.setButton(i+1, allButtons[i]);
    }

    

  Joystick.sendState();
  delay(5);
}
