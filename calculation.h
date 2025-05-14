const int calculationTime = 1000;

u_int32_t prevTime = millis();
double prevMass = -1;
double mass = -1;
double deltaTime = -1;
double calculated = -1;

float forceMultiplier = 0.27;
float forceOffset = 66.7;


int rotations = 0;

std::vector<double> forceValues;

void addForce(double force) {
  forceValues.push_back(force);
}

void clearForces() {
  forceValues.clear();
}

void addRotation() {
  rotations++;
}

double trueCalculateMass(float reading) {
  uint32_t curTime = millis();

  if (prevTime == curTime) return -1;

  double deltaTimeMs = (double) (curTime - prevTime);
  deltaTime = deltaTimeMs / 1000;

  calculated = reading / pow(1.0 / deltaTime, 2);
  double offsetReading = forceMultiplier * (calculated - forceOffset);

  prevTime = curTime;
  mass = offsetReading;

  // displayCalculatedMass(offsetReading, deltaTime, reading)

  return offsetReading;
}
