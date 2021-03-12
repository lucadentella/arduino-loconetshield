// LnCurrentSensor v1.0
// 
// activates a Loconet sensor if current is detected by a CT (current transformer) sensor
// requires a CT sensor like DL-CT1005A connected to pin A0 

#include <LocoNet.h>

// address of the Loconet sensor
#define SENSOR_ADDRESS   2

// Sampling Parameters
const unsigned long sampleTime = 2000UL; 
const unsigned long numSamples = 100UL; 
const unsigned long sampleInterval = sampleTime / numSamples; 

bool sensorOn = false;

void setup() {

  Serial.begin(115200);
  Serial.println("LnCurrentSensor 1.0");
  Serial.println();
  
  // init Loconet library
  LocoNet.init();
  Serial.println("Init complete");
  Serial.println();
}

void loop() {

  float analogValue = readAvgValue(A0);

  if(analogValue > 0 && !sensorOn) {
    LocoNet.reportSensor(SENSOR_ADDRESS, 1);
    sensorOn = true;
    Serial.print("AnalogValue = ");
    Serial.print(analogValue);
    Serial.println(", reporting sensor ON");
  }
  
  if(analogValue == 0 && sensorOn) {
    LocoNet.reportSensor(SENSOR_ADDRESS, 0);
    sensorOn = false;
    Serial.print("AnalogValue = ");
    Serial.print(analogValue);
    Serial.println(", reporting sensor OFF");  
  }
}

float readAvgValue(int pin) {
  
  float accumulator = 0;
  unsigned int count = 0;
  unsigned long prevMicros = micros() - sampleInterval;
  
  while (count < numSamples) {
    if (micros() - prevMicros >= sampleInterval) {
      float adc_raw = (float) analogRead(pin);
      accumulator += adc_raw;
      count++;
      prevMicros += sampleInterval;
    }
  }

  float avg = (float)accumulator / (float)numSamples;
  return avg;  
}
