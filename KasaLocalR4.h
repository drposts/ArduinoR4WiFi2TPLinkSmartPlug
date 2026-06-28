#pragma once
#include <WiFiUdp.h>
#include <ArduinoJson.h>

class KasaLocalR4 {
public:
    KasaLocalR4(const char* ip);

    bool setRelay(bool state);
    bool getSysInfo(JsonDocument& doc);

private:
    bool sendCommand(const char* json);
    bool receiveResponse(JsonDocument& doc);

    const char* _ip;
    WiFiUDP _udp;
};
