# ESP32 BLE HID & Web Configuration Library

This comprehensive library provides a complete solution for ESP32 devices to function as BLE HID devices (keyboard and mouse) while also offering web-based configuration through a built-in web server and DNS server.

## Features

- **BLE HID Device**
  - Full keyboard support with all standard keys
  - Mouse movement and button control
  - Modifier key support (Shift, Ctrl, Alt, GUI)
  - Comprehensive key mapping
  
- **Web Server**
  - Built-in configuration interface
  - File upload capability
  - SPIFFS file system support
  - Custom route handling
  
- **DNS Server**
  - Captive portal support
  - Custom domain resolution
  
## Installation

1. Copy all the library files to your Arduino libraries folder
2. Include the necessary headers in your project
3. See the examples folder for usage demonstrations

## Usage

### BLE HID Device

```cpp
#include "BLEHIDDevice.h"

BLEHIDDevice bleHID;

void setup() {
    bleHID.init("ESP32 BLE HID");
}

void loop() {
    if (bleHID.isConnected()) {
        // Send a keyboard key
        bleHID.sendKeyboard(MOD_NONE, KEY_A);
        
        // Move mouse
        bleHID.sendMouse(10, 10, MOUSE_BUTTON_NONE);
    }
}
```

### Web Server

```cpp
#include "WebServerManager.h"

WebServerManager webServer("ESP32-Config", "password123");

void setup() {
    webServer.begin();
}

void loop() {
    webServer.handleClient();
}
```

### DNS Server

```cpp
#include "DNSServerManager.h"

DNSServerManager dnsServer;

void setup() {
    dnsServer.begin(WiFi.softAPIP());
}

void loop() {
    dnsServer.processNextRequest();
}
```

## API Reference

### BLEHIDDevice Class
- `init(const char* deviceName)`: Initialize the BLE HID device
- `sendKeyboard(uint8_t modifiers, uint8_t keycode)`: Send keyboard input
- `sendMouse(int8_t x, int8_t y, uint8_t buttons, int8_t wheel = 0)`: Send mouse input
- `isConnected()`: Check connection status

### WebServerManager Class
- `begin()`: Start the web server
- `handleClient()`: Process client requests
- `setupRoutes()`: Configure server routes
- `handleFileRead(String path)`: Serve files from SPIFFS

### DNSServerManager Class
- `begin(const IPAddress& localIP)`: Start the DNS server
- `processNextRequest()`: Handle DNS requests
- `stop()`: Stop the DNS server

## License

This library is released under the MIT License.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.