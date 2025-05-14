#include "FS.h"
#include "SD.h"
#include "SPI.h"

const char* path = "/data.txt";

char* formatReading(double accelerationMag, double imuMag) {
  static char buffer[100];

  snprintf(buffer,
           sizeof(buffer),
           "%u,%f,%lf,%lf,%lf,%lf\n",
           millis(),
           prevForce,
           deltaTime,
           calculated,
           mass,
           accelerationMag,
           imuMag);

  return buffer;
}

void appendReading(double accelerationMag, double imuMag) {
  Serial.printf("Appending to file: %s\n", path);

  File file = SD.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }

  if (file.print(formatReading(accelerationMag, imuMag))) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}


void writeHeader() {
  Serial.printf("Writing file: %s\n", path);

  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print("Time,Force,DeltaTime,Mass,Accelerometer Mag,Imu Mag\n")) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void setupSDCard() {
  Serial.println("Initializing SD card...");


  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  writeHeader();
}
