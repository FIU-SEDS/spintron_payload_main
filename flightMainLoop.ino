void setupMainLoopFlight() {
  turnOnMotor();
}

void mainLoopFlight() {

  if (mass != prevMass) { // The mass had updated
    Serial.print("Saved reading data to SD card!");

    appendReading(AccMagMovingAvg(), imuAccelerationMagMovingAvg());

    prevMass = mass;
  }
}
