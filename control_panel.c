/* Complete USB Joystick Example
   Teensy becomes a USB joystick with 16 or 32 buttons and 6 axis input

   You must select Joystick from the "Tools > USB Type" menu

   Pushbuttons should be connected between the digital pins and ground.
   Potentiometers should be connected to analog inputs 0 to 5.

   This example code is in the public domain.
*/

// Configure the number of buttons.  Be careful not
// to use a pin for both a digital button and analog
// axis.  The pullup resistor will interfere with
// the analog voltage.
#include <ResponsiveAnalogRead.h>

ResponsiveAnalogRead analogOne(A0, true);
ResponsiveAnalogRead analogTwo(A1, true);
ResponsiveAnalogRead analogThree(A2, true);
ResponsiveAnalogRead analogFour(A3, true);
ResponsiveAnalogRead analogFive(A4, true);
ResponsiveAnalogRead analogSix(A5, true);

const int numButtons = 16;  // 16 for Teensy, 32 for Teensy++
byte allButtons[numButtons];
int greenPin =  23;
int bluePin =  21;
int redPin =  22;
int upper_layer = 20;
int lower_layer = 12;
int bPins[] = {8,9,10,11};
int midPins[] = {25, 26, 27, 28};
int shiftPins[] = {29, 30, 31, 32};

void setup() {
//  Serial.begin(9600);
  // configure the joystick to manual send mode.  This gives precise
  // control over when the computer receives updates, but it does
  // require you to manually call Joystick.send_now().
  Joystick.useManualSend(true);
  for (int i=0; i<14; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  pinMode(upper_layer, INPUT_PULLUP);
  pinMode(lower_layer, INPUT_PULLUP);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // read 6 analog inputs and use them for the joystick axis
  analogOne.update();
  analogTwo.update();
  analogThree.update();
  analogFour.update();
  analogFive.update();
  analogSix.update();
  
  Joystick.X(analogOne.getValue());
  Joystick.Y(analogTwo.getValue());
  Joystick.Z(analogThree.getValue());
  Joystick.Zrotate(analogFour.getValue());
  Joystick.sliderLeft(analogFive.getValue());
  Joystick.sliderRight(analogSix.getValue());
  
  if (digitalRead(lower_layer) == 0) {
    analogWrite(redPin, 0);
    analogWrite(bluePin, 5);
    analogWrite(greenPin, 0);

    for (int i=0; i<8; i++) {
      if (digitalRead(i)) {
        allButtons[i] = 0;
      } else {
        allButtons[i] = 1;
      }
    Joystick.button(i + 17, allButtons[i]);
    }
    for (int i=0; i<4; i++) {
      int bPin = bPins[i];
      if (digitalRead(bPin)) {
        allButtons[bPin] = 0;
      } else {
        allButtons[bPin] = 1;
      }
      Joystick.button(shiftPins[i], allButtons[bPin]);
    }
  } else if (digitalRead(upper_layer) == 0) {
    analogWrite(redPin, 5);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);

    for (int i=0; i<8; i++) {
      if (digitalRead(i)) {
        allButtons[i] = 0;
      } else {
        allButtons[i] = 1;
      }
    Joystick.button(i + 9, allButtons[i]);
    }
    for (int i=0; i<4; i++) {
      int bPin = bPins[i];
      if (digitalRead(bPin)) {
        allButtons[bPin] = 0;
      } else {
        allButtons[bPin] = 1;
      }
      Joystick.button(shiftPins[i], allButtons[bPin]);
    }
  } else {
    analogWrite(redPin, 0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 5);

    for (int i=0; i<8; i++) {
      if (digitalRead(i)) {
        allButtons[i] = 0;
      } else {
        allButtons[i] = 1;
      }
    Joystick.button(i + 1, allButtons[i]);
    }
    for (int i=0; i<4; i++) {
      int bPin = bPins[i];
      if (digitalRead(bPin)) {
        allButtons[bPin] = 0;
      } else {
        allButtons[bPin] = 1;
      }
      Joystick.button(midPins[i], allButtons[bPin]);
    }
  }

  Joystick.send_now();

  // a brief delay, so this runs "only" 200 times per second
  delay(5);
}
