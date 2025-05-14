#include <esp_now.h>
#include <WiFi.h>

// this will be setup when a packet is received with transmitter MAC adddress
uint8_t broadcastAddress[] = { 0x64, 0xE8, 0x33, 0xB8, 0xFF, 0xFC };

float prevForce = -1;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  float force;
  bool rotation;
} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message BME280Readings;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) success = "Delivery Success :)";
  else success = "Delivery Fail :(";
}

// Callback when data is received
void OnDataRecv(const esp_now_recv_info_t* mac, const unsigned char* incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  // if no broadcast address set it up to transmitter MAC
  if (broadcastAddress[0] == 0) {
    memcpy(broadcastAddress, mac->src_addr, 6);       // set broadcasrAddress to received MAC address
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);  // Register peer
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Failed to add peer");
      return;
    }
  }
  // display transmitter MAC address and copy data
  // Serial.printf("From %02X:%02X:%02X:%02X:%02X:%02X",
  //               mac->src_addr[0], mac->src_addr[1], mac->src_addr[2], mac->src_addr[3], mac->src_addr[4], mac->src_addr[5]);
  // Serial.printf(" Bytes received: %d\n", len);
  // Serial.printf("")

  if (incomingReadings.rotation) {
    // addRotation();
    Serial.println("Did rotation");

    trueCalculateMass(prevForce);
  } else if (incomingReadings.force != -1) {
    forceValues.push_back(incomingReadings.force);

    // Serial.print("Got reading: ");
    // Serial.println(incomingReadings.force);
    // addForce(incomingReadings.force);

    prevForce = incomingReadings.force;
  }
}

void setupMaster() {
  Serial.println("\n\n **** ESP-NOW receiver *****");
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  delay(100);  // short delay for initialisation
  Serial.print("WiFi MAC address ");
  Serial.println(WiFi.macAddress());
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  Serial.print("ESP-NOW initialised");
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
