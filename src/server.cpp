#include "server.hpp"

AsyncWebServer server(80);
AsyncWebSocket ws("/websocket");

esp_err_t init_server() {
  ws.onEvent(ws_event);
  server.addHandler(&ws);

  // start SPIFFS
  if (!SPIFFS.begin()) {
    return ESP_FAIL;
  }

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.begin();

  return ESP_OK;
}

void ws_event(AsyncWebSocket *server, AsyncWebSocketClient *client,
              AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(),
                    client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA: {
      AwsFrameInfo *info = (AwsFrameInfo *)arg;
      if (info->final && info->index == 0 && info->len == len &&
          info->opcode == WS_TEXT) {
        data[len] = 0;

        if (data[0] == 'f') {
          digitalWrite(4, !digitalRead(4));
        }
        // if data === toggle
        // if (strcmp((char *)data, "x") == 0) {
        //   ws.textAll(String(x));
        // }
      }
    } break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void ws_cleanup() { ws.cleanupClients(); }

void ws_send_fb(camera_fb_t *fb) { ws.binaryAll(fb->buf, fb->len); }
