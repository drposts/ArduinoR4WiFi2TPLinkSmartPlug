#include <WiFiS3.h>
#include <KasaLocalR4.h>

const char* ssid = "YOUR_WIFI";
const char* pass = "YOUR_PASS";

KasaLocalR4 plug("192.168.1.52");

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) delay(100);

    Serial.println("Connected.");
}

void loop() {
    plug.setRelay(true);
    Serial.println("ON");
    delay(3000);

    plug.setRelay(false);
    Serial.println("OFF");
    delay(3000);
}
