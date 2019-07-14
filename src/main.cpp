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
    if(request->url() == "/rick.ogg") {
      request->send(SPIFFS, "/rick.ogg", "audio/ogg");
    }
    else if(request->url() == "/giphy.webp") {
       request->send(SPIFFS, "/giphy.webp", "image/webp");
    }
    else if(request->url() == "/bootstrap.min.css") {
       request->send(SPIFFS, "/bootstrap.min.css", "text/css");
    }
    else if(request->url() == "/scrolling-nav.css") {
       request->send(SPIFFS, "/scrolling-nav.css", "text/css");
    }
    else if(request->url() == "/logo-ironwifi.png") {
       request->send(SPIFFS, "/logo-ironwifi.png", "image/png");
    }
    else if(request->url() == "/"){
      request->send(SPIFFS, "/index.html", "text/html");
    }
    else {
      request->send( 404, "text/html", "NOT FOUND!" );
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
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 0, 0));
  WiFi.softAP("FREE WIFI");
  dnsServer.start(DNS_PORT, "*", apIP);
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  server.begin();
}

void loop()
{
  dnsServer.processNextRequest();
}