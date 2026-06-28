#include "KasaLocalR4.h"
#include "utility/KasaXor.h"

KasaLocalR4::KasaLocalR4(const char* ip) : _ip(ip) {
    _udp.begin(9999);
}

bool KasaLocalR4::sendCommand(const char* json) {
    uint8_t buf[512];
    size_t len = strlen(json);

    memcpy(buf, json, len);
    kasaXor(buf, len);

    _udp.beginPacket(_ip, 9999);
    _udp.write(buf, len);
    return _udp.endPacket();
}

bool KasaLocalR4::receiveResponse(JsonDocument& doc) {
    uint32_t start = millis();
    uint8_t buf[512];

    while (millis() - start < 1000) {
        int packetSize = _udp.parsePacket();
        if (packetSize > 0) {
            int n = _udp.read(buf, min(packetSize, 512));
            kasaXor(buf, n);
            DeserializationError err = deserializeJson(doc, buf, n);
            return !err;
        }
    }
    return false;
}

bool KasaLocalR4::setRelay(bool state) {
    StaticJsonDocument<128> cmd;
    cmd["system"]["set_relay_state"]["state"] = state;

    char json[128];
    serializeJson(cmd, json);

    return sendCommand(json);
}

bool KasaLocalR4::getSysInfo(JsonDocument& doc) {
    StaticJsonDocument<128> cmd;
    cmd["system"]["get_sysinfo"] = JsonObject();

    char json[128];
    serializeJson(cmd, json);

    if (!sendCommand(json)) return false;
    return receiveResponse(doc);
}
