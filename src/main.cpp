#include <Arduino.h>
#include <DNSServer.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

AsyncWebServer server(80);

const byte DNS_PORT = 53;
IPAddress apIP(172, 0, 0, 1);
DNSServer dnsServer;

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    if(request->url() == "/rick.mp3") {
      request->send(SPIFFS, "/rick.mp3", "audio/mpeg");
    }
    else if(request->url() == "/giphy.webp") {
       request->send(SPIFFS, "/giphy.webp", "image/webp");
    }
    else {
      request->send(SPIFFS, "/index.html", "text/html");
    }
  }
};

void setup()
{
  if (!SPIFFS.begin(true))
  {
    return;
  }
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("FREE WIFI");
  dnsServer.start(DNS_PORT, "*", apIP);
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  server.begin();
}

void loop()
{
  dnsServer.processNextRequest();
}