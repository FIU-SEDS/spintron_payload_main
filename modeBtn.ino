const int MODE_BTN_PIN = 8;

void modeBtnSetup() {
  pinMode(MODE_BTN_PIN, INPUT_PULLDOWN);
}

bool modeBtnPressed() {
  return digitalRead(MODE_BTN_PIN) == HIGH;
}