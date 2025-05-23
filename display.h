#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define DISPLAY_TYPE Adafruit_SSD1306

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("Display Init succeeded");

  // Clear the buffer
  display.display();
  delay(10);
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.write("Mass Measuring Device");
  display.write("\n");
  display.write("Operation Gaybriel");

  display.display();
  // delay(200);
}


void displayCalculatedMass(double mass, double deltaTime, float reading) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);

  char buf[32];
  snprintf(buf, 32, "%0.3lf", mass);

  display.write(buf);
  display.write(" g");
  display.write("\n");

  display.write("RPS: ");

  snprintf(buf, 32, "%0.3lf", 1.0 / deltaTime);
  display.write(buf);

  display.write("Read: ");
  snprintf(buf, 32, "%0.3f", reading);
  display.write(buf);

  display.display();
}
