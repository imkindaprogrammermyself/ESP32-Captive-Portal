# ESP32-Captive-Portal
Converts your ESP32 into a captive portal. It uses [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncTCP) library. In order for the captive portal to work on some devices, I have to use non local IP address for `WiFi.softAPConfig();`
