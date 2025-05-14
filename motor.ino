const int MOTOR_PIN = 9;

const int MOTOR_SPEED = 300; // Maximum speed (4095)

void setupMotor() {
  pinMode(MOTOR_PIN, OUTPUT);
  turnOffMotor();
}

void turnOnMotor() {
  analogWrite(MOTOR_PIN, MOTOR_SPEED);
}


void turnOffMotor() {
  analogWrite(MOTOR_PIN, 0);
}
