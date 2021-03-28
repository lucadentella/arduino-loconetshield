#include <LocoNet.h>

lnMsg *LnPacket;
LnBuf LnTxBuffer;

void setup() {
  // First initialize the LocoNet interface
  LocoNet.init();

  // Configure the serial port for 19200 baud
  Serial.begin(19200);
}

void loop() {

  // check for packets coming from the Loconet bus
  LnPacket = LocoNet.receive();  
  
  if(LnPacket) {
    uint8_t msgLen = getLnMsgSize(LnPacket);
    for (uint8_t x = 0; x < msgLen; x++)
      Serial.write(LnPacket->data[x]);
  }


  // check for packets coming from the serial port
  if(Serial.available()) { 
    
    uint8_t inByte = Serial.read() & 0xFF;
    addByteLnBuf(&LnTxBuffer, inByte);
    
    LnPacket = recvLnMsg( &LnTxBuffer );
    if(LnPacket) LocoNet.send(LnPacket);
  }
}
