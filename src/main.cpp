#include <Arduino.h>
#include "configuration.hpp"
#include "wifi.hpp"

void setup() {
  // load default configuration
  Configuration config = Configuration::load();

  // init wifi AP
  init_wifi(config);
}

void loop() {
    delay(1000);
}
