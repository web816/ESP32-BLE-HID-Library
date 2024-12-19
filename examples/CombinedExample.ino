#include "BLEHIDDevice.h"
#include "WebServerManager.h"
#include "DNSServerManager.h"
#include "KeyboardLayout.h"

// Create instances of our managers
BLEHIDDevice bleHID;
WebServerManager webServer("ESP32-Config", "password123");
DNSServerManager dnsServer;

void setup() {
    Serial.begin(115200);
    
    // Initialize BLE HID
    bleHID.init("ESP32 BLE HID");
    
    // Initialize Web Server
    webServer.begin();
    
    // Initialize DNS Server
    dnsServer.begin(WiFi.softAPIP());
    
    Serial.println("All services started!");
}

void loop() {
    // Handle DNS requests
    dnsServer.processNextRequest();
    
    // Handle Web Server clients
    webServer.handleClient();
    
    // Example: Send keyboard input
    if (bleHID.isConnected()) {
        // Type "Hello" with a 1-second delay
        bleHID.sendKeyboard(MOD_NONE, KEY_H);
        delay(100);
        bleHID.sendKeyboard(MOD_NONE, KEY_E);
        delay(100);
        bleHID.sendKeyboard(MOD_NONE, KEY_L);
        delay(100);
        bleHID.sendKeyboard(MOD_NONE, KEY_L);
        delay(100);
        bleHID.sendKeyboard(MOD_NONE, KEY_O);
        delay(1000);
        
        // Move mouse in a square pattern
        bleHID.sendMouse(50, 0, MOUSE_BUTTON_NONE);  // Right
        delay(100);
        bleHID.sendMouse(0, 50, MOUSE_BUTTON_NONE);  // Down
        delay(100);
        bleHID.sendMouse(-50, 0, MOUSE_BUTTON_NONE); // Left
        delay(100);
        bleHID.sendMouse(0, -50, MOUSE_BUTTON_NONE); // Up
        delay(1000);
    }
}