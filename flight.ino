bool isInFlight = false;
bool prevIsInApogee = false;

bool firstEnteringMainLoopFlight = true;
uint32_t apogeeStartTime = -1;

const uint32_t APOGEE_TIME = 12 * 1000;

const uint32_t FLIGHT_TIME_TILL_APOGEE = (24 - 4) * 1000;
uint32_t flightStartTime = -1;
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
      flightStartTime = millis();
    } else {
      return;
    }
  }

  if (doneApogee) return;

  // Entering apogee by checking time
  if (!prevIsInApogee && (millis() - flightStartTime) >= FLIGHT_TIME_TILL_APOGEE ) {
    Serial.println("Entering apogee");

    prevIsInApogee = true;
    setupMainLoopFlight();
    apogeeStartTime = millis();

    // Exiting apogee
  } else if (prevIsInApogee && (millis() - apogeeStartTime) >= APOGEE_TIME) {
    Serial.println("Exiting apogee");

    prevIsInApogee = false;
    doneApogee = true;
    turnOffMotor();
    return;

    // Not in apogee
  } else if (prevIsInApogee) {
    mainLoopFlight();
  }

}
