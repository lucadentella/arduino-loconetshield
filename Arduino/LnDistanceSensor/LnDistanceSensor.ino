// LnDistanceSensor v1.0
// 
// activates a Loconet sensor if an object is near the TOF sensor
// requires a vl53l0x sensor an Pololu library (https://github.com/pololu/vl53l0x-arduino)

#include <LocoNet.h>
#include <Wire.h>
#include <VL53L0X.h>

// address of the Loconet sensor
#define SENSOR_ADDRESS   2

// minimum distance to activate the sensor (in mm)
#define ON_DISTANCE     50

// threshold to avoid continous changes
#define THRESHOLD        5


VL53L0X sensor;
bool sensorOn = false;

void setup() {

  Serial.begin(115200);
  Serial.println("LnDistanceSensor 1.0");
  Serial.println();
  
  // init Loconet library
  LocoNet.init();

  // init Wire library and sensor (for high accuracy)
  Wire.begin();
  sensor.setTimeout(500);
  sensor.setMeasurementTimingBudget(200000);
  if (!sensor.init()) {
    Serial.println("VL53L0X sensor init failed");
    while(1) {};
  }
  
  Serial.println("Init complete");
  Serial.println();
}

void loop() {

  uint16_t distance = sensor.readRangeSingleMillimeters();

  if(distance < ON_DISTANCE - THRESHOLD && !sensorOn) {
    LocoNet.reportSensor(SENSOR_ADDRESS, 1);
    sensorOn = true;
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(", reporting sensor ON");
  }
  
  if(distance > ON_DISTANCE + THRESHOLD && sensorOn) {
    LocoNet.reportSensor(SENSOR_ADDRESS, 0);
    sensorOn = false;
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(", reporting sensor OFF");  
  }
}
