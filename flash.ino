#include "nvs_flash.h"

static const char* TAG = "spintron_main";
nvs_handle_t nvsHandle;

const double forceMultipierScalingFactor = 1000000;
const double forceOffsetScalingFactor = 1000000;

void setupFlash() {
  nvs_flash_init();
  esp_err_t err = nvs_open("namespace", NVS_READWRITE, &nvsHandle);

forceMultiplier = getForceMultiplier();
forceOffset += getForceOffset();

//   nvs_set_str(nvsHandle, "test", "Hello World!");
//   nvs_commit(nvsHandle);
  nvs_close(nvsHandle);


  Serial.println("Done!");
}

float getForceMultiplier() {
    int32_t value = 1;

    esp_err_t read_err = nvs_get_i32(nvsHandle, "forceMultiplier", &value);

    if (read_err == ESP_OK) {
        return parseMultipier(value, forceMultipierScalingFactor);
    }

    if (read_err == ESP_ERR_NVS_NOT_FOUND) {
        Serial.printf("forceMultiplier is unset, using default value");

        // Handle the case where the key doesn't exist (e.g., set a default value)
        esp_err_t write_err = nvs_set_i32(nvsHandle, "forceMultiplier", forceMultipierScalingFactor);
        if(write_err == ESP_OK){
            Serial.println("Key Created and Set with default value");
            nvs_commit(nvsHandle);
        } else {
            Serial.printf("Error writing default value: (%s)\n", esp_err_to_name(write_err));
        }
    } else {
        Serial.printf("Error reading key 'forceMultiplier' (%s)!\n", esp_err_to_name(read_err));
    }

    return 1;
}

bool setForceMultiplier(float multiplier) {
  esp_err_t err = nvs_open("namespace", NVS_READWRITE, &nvsHandle);

    int32_t value = round(multiplier * forceMultipierScalingFactor);

    esp_err_t read_err = nvs_set_i32(nvsHandle, "forceMultiplier", value);

  nvs_commit(nvsHandle);
  nvs_close(nvsHandle);

    if (read_err == ESP_OK) {
        return true;
    }

    Serial.printf("Error reading key 'forceMultiplier' (%s)!\n", esp_err_to_name(read_err));


    return false;
}

double parseMultipier(int32_t value, float scalingFactor) {
    return (float)value / scalingFactor;
}

int32_t getForceOffset() {
    int32_t value = 0;

    esp_err_t read_err = nvs_get_i32(nvsHandle, "forceOffset", &value);

    if (read_err == ESP_OK) {
        return parseMultipier(value, forceOffsetScalingFactor);
    }

    if (read_err == ESP_ERR_NVS_NOT_FOUND) {
        Serial.printf("forceOffset is unset, using default value");

        // Handle the case where the key doesn't exist (e.g., set a default value)
        esp_err_t write_err = nvs_set_i32(nvsHandle, "forceOffset", 0);
        if(write_err == ESP_OK){
            Serial.println("Key Created and Set with default value");
            nvs_commit(nvsHandle);
        } else {
            Serial.printf("Error writing default value: (%s)\n", esp_err_to_name(write_err));
        }
    } else {
        Serial.printf("Error reading key 'forceOffset' (%s)!\n", esp_err_to_name(read_err));
    }

    return 0;
}

bool setForceOffset(float offset) {
  esp_err_t err = nvs_open("namespace", NVS_READWRITE, &nvsHandle);

    int32_t value = round(offset * forceOffsetScalingFactor);

    esp_err_t read_err = nvs_set_i32(nvsHandle, "forceOffset", value);

nvs_commit(nvsHandle);
  nvs_close(nvsHandle);

    if (read_err == ESP_OK) {
        return true;
    }

    Serial.printf("Error reading key 'forceOffset' (%s)!\n", esp_err_to_name(read_err));
    return false;
}

void commitFlash() {
    nvs_close(nvsHandle);
}

void closeFlash() {
    nvs_close(nvsHandle);
}
