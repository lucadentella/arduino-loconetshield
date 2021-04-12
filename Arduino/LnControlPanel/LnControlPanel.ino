// Loconet Control Panel
// button connected to PIN 4, LEDs connected to PIN 2-3

#include <LocoNet.h>

#define BUTTON_PIN  4
#define ST_LED_PIN  2
#define DIV_LED_PIN 3

#define TURNOUT_ADDRESS 1

lnMsg *LnPacket;
int turnoutDirection;
bool buttonPressed = false;

void setup() {

  Serial.begin(115200);
  Serial.println("LnControlPanel");

  LocoNet.init();
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ST_LED_PIN, OUTPUT);
  pinMode(DIV_LED_PIN, OUTPUT);

  // initial position, STRAIGHT
  turnoutDirection = 0;
  digitalWrite(ST_LED_PIN, HIGH);
  digitalWrite(DIV_LED_PIN, LOW);

  Serial.println("Init complete, ready to operate!");
}

void loop() {

  // process incoming Loconet messages
  LnPacket = LocoNet.receive();
  if(LnPacket) LocoNet.processSwitchSensorMessage(LnPacket);

  // button pressed
  if(digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {

    if(turnoutDirection == 0) turnoutDirection = 1;
    else turnoutDirection = 0;
    LocoNet.requestSwitch(TURNOUT_ADDRESS, 0, turnoutDirection);
    buttonPressed = true;
  }

  // button released
  else if(digitalRead(BUTTON_PIN) == HIGH) buttonPressed = false;
}


void notifySwitchRequest( uint16_t Address, uint8_t Output, uint8_t Direction ) {
  
  if(Address == TURNOUT_ADDRESS) {

    turnoutDirection = Direction;
    if(turnoutDirection == 0) {
      digitalWrite(ST_LED_PIN, HIGH);
      digitalWrite(DIV_LED_PIN, LOW);
    } else {
      digitalWrite(ST_LED_PIN, LOW);
      digitalWrite(DIV_LED_PIN, HIGH);       
    }
  }
}
