# ArduinoR4WiFi2TPLinkSmartPlug
Arduino Library for R4 WiFi to control TP Link Kasa Smart Plug (Local Network mode)

# KasaLocalR4  
### Local Network Control Library for TP‑Link Kasa Smart Plugs  
### Designed for **Arduino Uno R4 WiFi** and **WiFiS3‑based boards**

---

## 📦 Overview

**KasaLocalR4** is a lightweight Arduino library that enables **local network control** of TP‑Link Kasa smart plugs (including EP10, HS103, HS105, HS200, KP115, KP125, and similar models).  
It communicates directly with the device over **UDP port 9999**, using the official Kasa **XOR‑encrypted JSON protocol** — **no cloud required**.

This library is written specifically for:

- **Arduino Uno R4 WiFi**  
- **Arduino WiFiS3‑based boards**  
- **Nano ESP32 (Arduino core)**  
- Any board supporting **WiFiUDP** and **ArduinoJson**

It is a clean rewrite of the ESP32‑only libraries, adapted for the Uno R4 WiFi’s **WiFiS3** networking stack.

---

## ✨ Features

- 🔌 Turn Kasa smart plugs **ON/OFF** locally  
- 📡 Query device information (`get_sysinfo`)  
- 🔐 XOR encryption (Kasa protocol)  
- 🌐 UDP transport via `WiFiUDP`  
- 📄 JSON building/parsing using **ArduinoJson**  
- 🚫 No cloud, no account, no Kasa app required  
- 🧩 Works with EP10 and other Kasa models using the classic XOR protocol  
- 🧼 Clean, modern Arduino‑style API

---

## 📚 Supported Devices

This library supports all Kasa devices using the **XOR‑encrypted UDP protocol**, including:

- EP10  
- HS103 / HS105  
- HS200  
- KP115 / KP125  
- Many other Kasa plugs and switches

If your device responds on **UDP port 9999**, it is compatible.

---

## 🔧 Installation

### Option 1 — Install from ZIP
1. Download the repository as a ZIP  
2. Arduino IDE → **Sketch → Include Library → Add .ZIP Library…**  
3. Select the ZIP file

### Option 2 — Clone into your Arduino libraries folder
```
Documents/Arduino/libraries/KasaLocalR4/
```

### Dependencies
This library requires:

📦 **ArduinoJson**  
[https://arduinojson.org/](https://arduinojson.org/)

Install via Library Manager:

```
Tools → Manage Libraries → "ArduinoJson"
```

---

## 🚀 Quick Start Example

```cpp
#include <WiFiS3.h>
#include <KasaLocalR4.h>

const char* ssid = "YOUR_WIFI";
const char* pass = "YOUR_PASS";

KasaLocalR4 plug("192.168.1.52");   // IP of your Kasa device

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }

    Serial.println("Connected to WiFi.");
}

void loop() {
    plug.setRelay(true);   // Turn ON
    Serial.println("ON");
    delay(3000);

    plug.setRelay(false);  // Turn OFF
    Serial.println("OFF");
    delay(3000);
}
```

---

## 🧠 How It Works

Kasa smart plugs use a simple protocol:

### 1. JSON command  
Example:
```json
{"system":{"set_relay_state":{"state":1}}}
```

### 2. XOR encryption  
Each byte is XOR’d with a rolling key starting at `0xAB`.

### 3. UDP transport  
Encrypted bytes are sent to:

```
UDP port: 9999
Protocol: XOR-encrypted JSON
```

### 4. Device responds with encrypted JSON  
The library decrypts and parses it using **ArduinoJson**.

---

## 📘 API Reference

### Constructor
```cpp
KasaLocalR4 plug("192.168.1.52");
```

### Turn plug ON/OFF
```cpp
plug.setRelay(true);
plug.setRelay(false);
```

### Get device info
```cpp
StaticJsonDocument<512> doc;
if (plug.getSysInfo(doc)) {
    serializeJsonPretty(doc, Serial);
}
```

### Low‑level send/receive
```cpp
plug.sendCommand(jsonString);
plug.receiveResponse(doc);
```

---

## 📁 Project Structure

```
KasaLocalR4/
 ├── src/
 │    ├── KasaLocalR4.h
 │    ├── KasaLocalR4.cpp
 │    └── utility/
 │         └── KasaXor.h
 ├── examples/
 │    └── BasicControl/
 │         └── BasicControl.ino
 ├── library.properties
 ├── README.md
 └── LICENSE
```

## 🧪 Testing Your Device

To verify your Kasa plug supports local control:

1. Find its IP address (router DHCP table)  
2. Run the example sketch  
3. Watch Serial Monitor for ON/OFF messages  
4. If the device responds, local control is working

---

## 🛠️ Troubleshooting

### Device doesn’t respond
- Ensure your Uno R4 WiFi is on the **same network**  
- Verify the plug’s IP address  
- Some Kasa models require a reboot after pairing  
- EP10 sometimes needs a second command after wake‑up

### JSON parsing errors
Enable debug prints:

```cpp
serializeJsonPretty(doc, Serial);
```

### No UDP packets received
Some routers block LAN‑LAN UDP.  
Enable “client isolation off” or “allow peer‑to‑peer”.

---

## 📄 License

MIT License — free for commercial and personal use.

---

## 🤝 Contributing

Pull requests are welcome!  
Feel free to add:

- EP10 securePassthrough support  
- AES‑encrypted protocol (newer Kasa models)  
- Additional device types  
- Async UDP support  
- PlatformIO examples  

---

## ⭐ Acknowledgments

This library is inspired by earlier TP Link Kasa and ESP32‑based Kasa projects.  
I have re‑engineered the communication protocols for the Arduino Uno R4 WiFi ecosystem.

Special thanks to:

- tplink-smartplug by softScheck
      The Full Story: Reverse Engineering the TP-Link HS110
          https://www.softscheck.com/en/reverse-engineering-tp-link-hs110/
      TP-Link WiFi SmartPlug Client and Wireshark Dissector
          https://github.com/softScheck/tplink-smartplug
          
- KasaSmartPlug by Kris Jearakul
      Arduino Library for ESP32 to control TP Link Kasa Smart Plug (Local Network mode) 
          https://github.com/kj831ca/KasaSmartPlug/blob/main/README.md
  
- **ArduinoJson** by Benoit Blanchon
          https://arduinojson.org

- Everyone who contributes device protocol logs

