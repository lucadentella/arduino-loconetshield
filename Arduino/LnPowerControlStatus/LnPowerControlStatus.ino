#include <LocoNet.h>

#define LED_PIN     2
#define BUTTON_PIN  3

bool isPowerOn = false;
bool buttonWasDown = false;

void setup() {

  LocoNet.init();
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop() {

  lnMsg *LnPacket = LocoNet.receive();
  if(LnPacket) LocoNet.processSwitchSensorMessage(LnPacket);

  checkButton();
}

void notifyPower(uint8_t State) {

    if(State == 1) digitalWrite(LED_PIN, HIGH);
    else digitalWrite(LED_PIN, LOW);
}

void checkButton() {

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
