bool isInFlight = false;
bool prevIsInApogee = false;

bool firstEnteringMainLoopFlight = true;
uint32_t apogeeStartTime = -1;

const uint32_t APOGEE_TIME = 45000;
bool doneApogee = false;

void setupFlight() {

  while(setupIMU()) {
    Serial.println("IMU setup failed, retrying...");
    delay(1000);
  };

  // while (setupAccelerometer()) {
  //   Serial.println("Accelerometer setup failed, retrying...");
  //   delay(1000);
  // };

  setupMotor(); // This cannot fail
  Serial.println("Setup payload motor");

  Serial.println("Flight setup complete");
}

void loopFlight() {
  // Check if the device is in flight
  // If not wait until it is
  if (!isInFlight) {
    if (checkIsInFlight()) {
      Serial.println("Entering flight");
      isInFlight = true;
    } else {
      return;
    }
  }

  if (doneApogee) return;

  // Entering apogee
  if (!prevIsInApogee && isInApogee()) {
    Serial.println("Entering apogee");

    prevIsInApogee = true;
    setupMainLoopFlight();
    apogeeStartTime = millis();

    // Exiting apogee
  } else if (prevIsInApogee && (millis() - apogeeStartTime) >= APOGEE_TIME) {
    Serial.println("Exiting apogee");

    prevIsInApogee = false;
    doneApogee = true;
    return;

    // Not in apogee
  } else if (prevIsInApogee) {
    mainLoopFlight();
  }

}
