#include <LocoNet.h>

#define LED_PIN  2

void setup() {

  LocoNet.init();
  pinMode(LED_PIN, OUTPUT);
}


void loop() {

  lnMsg *LnPacket = LocoNet.receive();
  if(LnPacket) LocoNet.processSwitchSensorMessage(LnPacket);
}

void notifyPower(uint8_t State) {

    if(State == 1) digitalWrite(LED_PIN, HIGH);
    else digitalWrite(LED_PIN, LOW);
}
