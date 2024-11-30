#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration {
 public:
  struct WifiConfiguration {
    char *ssid = "SSID";
    char *password = "PASSWORD";
    char *mdns = "MDNS";
  } wifi;

  static Configuration load();
};

#endif
