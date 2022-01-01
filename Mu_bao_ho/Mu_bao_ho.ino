#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "SPI.h"
#include "ModuleOled.h"
#include "SensorCO.h"
#include "SensorMPU.h"
#include "SensorSHT3x.h"
#include "SensorGPS.h"
#include "ModuleSDCard.h"
#include "ModuleSim.h"


void setup() {
  setupOled();
  setupCO();
  setupGPS();
  setupMPU();
  setupSHT3x();
  setupSim();
  setupSD();
}

void loop() {
  oled_loop();
  readCO();
  readGPS();
  readSHT3x();
  logData();
  sendData2Server();
}
