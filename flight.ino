bool isInFlight = false;
bool prevIsInApogee = false;

bool firstEnteringMainLoopFlight = true;

void setupFlight() {

  while(setupIMU()) {
    Serial.println("IMU setup failed, retrying...");
    delay(1000);
  };

  while (setupAccelerometer()) {
    Serial.println("Accelerometer setup failed, retrying...");
    delay(1000);
  };

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

  // Entering apogee
  if (!prevIsInApogee && isInApogee()) {
    Serial.println("Entering apogee");

    prevIsInApogee = true;

    // Exiting apogee
  } else if (prevIsInApogee && !isInApogee()) {
    Serial.println("Exiting apogee");

    prevIsInApogee = false;

    // Not in apogee
  } else if (!isInApogee()) {
    return;
  }

  mainLoopFlight();
}
