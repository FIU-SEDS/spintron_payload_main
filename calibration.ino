#define COMMIT_BTN_PIN 18

#define CALI_FMULT_UP 7
#define CALI_FMULT_DOWN 15

#define CALI_FOFFSET_UP 16
#define CALI_FOFSSET_DOWN 17

const float FORCE_MULTIPLIER_STEP = 0.001;
const float FORCE_OFFSET_STEP = 0.01;

void setupCalibration() {
  Serial.println("Setting up calibration!");

  pinMode(COMMIT_BTN_PIN, INPUT_PULLDOWN);

  pinMode(CALI_FMULT_UP, INPUT_PULLDOWN);
  pinMode(CALI_FMULT_DOWN, INPUT_PULLDOWN);

  pinMode(CALI_FOFFSET_UP, INPUT_PULLDOWN);
  pinMode(CALI_FOFSSET_DOWN, INPUT_PULLDOWN);

  // display.clearDisplay();

  display.write("\n");
  display.write("Entering calibration ...");

  display.display();
}

void loopCalibration() {
  if (mass != prevMass) { // The mass had updated!
    displayCalculatedMass(mass, deltaTime, prevForce);
  }
  // uint32_t currentTime = millis();
  // if (startTime + calculationTime >= currentTime) {
  //   double mass = calculateMass();

  //   Serial.print("Found mass: ");
  //   Serial.println(mass);

  //   startTime = millis();
  // }

  if (digitalRead(CALI_FMULT_UP) == HIGH) {
    forceMultiplier += FORCE_MULTIPLIER_STEP;
  } else if (digitalRead(CALI_FMULT_DOWN) == HIGH) {
    forceMultiplier -= FORCE_MULTIPLIER_STEP;
  } else if (digitalRead(CALI_FOFFSET_UP) == HIGH) {
    forceOffset += FORCE_OFFSET_STEP;
  } else if (digitalRead(CALI_FOFSSET_DOWN) == HIGH) {
    forceMultiplier -= FORCE_OFFSET_STEP;
  }

  if (digitalRead(COMMIT_BTN_PIN) == HIGH) {
    setForceMultiplier(forceMultiplier);
    setForceOffset(forceOffset);

    Serial.println("Saved calibration values!");

    display.clearDisplay();
    display.write("Saved calibration values!");
    display.display();
  }

  delay(10);
}

bool isCommitBtnPressed() {
  return digitalRead(COMMIT_BTN_PIN) == HIGH;
}
