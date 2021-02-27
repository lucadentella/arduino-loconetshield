#include <LocoNet.h>

#define BUTTON_PIN  2

bool isPowerOn = false;
bool buttonWasDown = false;

void setup() {

  LocoNet.init();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop() {

  // button pressed
  if(digitalRead(BUTTON_PIN) == LOW && !buttonWasDown) {

    // toggle power status
    if(isPowerOn) {
      LocoNet.reportPower(0);
      isPowerOn = false;
    } else {
      LocoNet.reportPower(1);
      isPowerOn = true;      
    }
    buttonWasDown = true;
  }

  // button released
  else if(digitalRead(BUTTON_PIN) == HIGH && buttonWasDown)
    buttonWasDown = false;
}
