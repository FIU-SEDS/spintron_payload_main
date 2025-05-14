#include <Wire.h>
#include <vector>

#include "display.h"
#include "calculation.h"
#include "master.h"
#include "sd.h"

bool modeCalibration = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); delay(500);
  Serial.println();
  Serial.println("Starting main subsystem!");

  Wire.begin(4, 5);

  modeBtnSetup();
  setupDisplay();
  setupFlash();
  setupSDCard();

  setupMaster();

  if (modeBtnPressed()) {
    modeCalibration = true;
    setupCalibration();
  } else {
    setupFlight();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (modeCalibration) {
    loopCalibration();
  } else {
    loopFlight();
  }
}
