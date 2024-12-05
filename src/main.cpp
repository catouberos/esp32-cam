#include <Arduino.h>

#include "camera.hpp"
#include "esp32-hal-gpio.h"
#include "esp_err.h"
#include "server.hpp"
#include "wifi.hpp"

esp_err_t fb_status = ESP_OK;

void setup() {
  Serial.begin(115200);
  Configuration config = Configuration::load();

  pinMode(33, OUTPUT);

  Serial.println("Initiating camera...");
  esp_err_t err = init_camera();
  if (err == ESP_FAIL) {
    Serial.printf("Camera failed to init, error: 0x%x\n", err);
  }

  Serial.println("Initiating WiFi connection...");
  err = init_wifi(config);
  if (err == ESP_FAIL) {
    Serial.printf("WiFi failed to init, error: 0x%x\n", err);
  }

  Serial.println("Initiating server...");
  err = init_server();
  if (err == ESP_FAIL) {
    Serial.printf("Server failed to init, error: 0x%x\n", err);
  }
}

void loop() {
  digitalWrite(33, HIGH);
  ws_cleanup();

  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    fb_status = ESP_FAIL;
  } else {
    fb_status = ESP_OK;
    ws_send_fb(fb);
  }

  esp_camera_fb_return(fb);
}
