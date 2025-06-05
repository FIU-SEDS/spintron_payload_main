const int MOTOR_PIN_1 = 3;
const int MOTOR_PIN_2 = 46;
const int MOTOR_PIN_PWM = 9;

const int MOTOR_SPEED = 120; // Maximum speed (255)

void setupMotor() {
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(MOTOR_PIN_PWM, OUTPUT);

  turnOffMotor();
}

void turnOnMotor() {
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, HIGH);

  analogWrite(MOTOR_PIN_PWM, MOTOR_SPEED);
}


void turnOffMotor() {
  digitalWrite(MOTOR_PIN_1, LOW);
  digitalWrite(MOTOR_PIN_2, LOW);

  analogWrite(MOTOR_PIN_PWM, 0);
}
