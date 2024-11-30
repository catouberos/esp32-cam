#ifndef SERVER_H
#define SERVER_H

#include <ESPAsyncWebServer.h>

#include "esp_camera.h"

esp_err_t init_server();
void ws_event(AsyncWebSocket *server, AsyncWebSocketClient *client,
              AwsEventType type, void *arg, uint8_t *data, size_t len);
void ws_cleanup();
void ws_send_fb(camera_fb_t *fb);

#endif
