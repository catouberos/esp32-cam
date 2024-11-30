#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration {
 public:
  struct WifiConfiguration {
    char *ssid = "SSID";
    char *password = "PASSWORD";
    char *mdns = "MDNS";
    char *ip = "192.168.1.120";
    char *gateway = "192.168.1.1";
    char *subnet = "255.255.255.0";
  } wifi;

  static Configuration load();
};

#endif
