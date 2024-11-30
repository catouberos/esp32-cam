#include "camera.hpp"

#include <Arduino.h>

#include "esp_camera.h"

esp_err_t init_camera() {
  if (CAM_PIN_PWDN != -1) {
    pinMode(CAM_PIN_PWDN, OUTPUT);
    digitalWrite(CAM_PIN_PWDN, LOW);
  }

  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK) {
    delay(100);
    return err;
  }

  // sensor_t *s = esp_camera_sensor_get();
  // s->set_framesize(s, FRAMESIZE_XGA);

  return ESP_OK;
}
