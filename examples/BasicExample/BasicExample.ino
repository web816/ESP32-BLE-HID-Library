#include <ESP32BLEHIDCombo.h>

BLEHIDDevice bleHID;

void setup() {
    Serial.begin(115200);
    
    if (!bleHID.init("ESP32 BLE HID")) {
        Serial.println("Failed to initialize BLE HID device!");
        return;
    }
    
    Serial.println("BLE HID device initialized successfully!");
}

void loop() {
    if (bleHID.isConnected()) {
        // Type "Hello"
        bleHID.sendKeyboard(Keyboard::NONE, Keyboard::H);
        delay(100);
        bleHID.sendKeyboard(Keyboard::NONE, Keyboard::E);
        delay(100);
        bleHID.sendKeyboard(Keyboard::NONE, Keyboard::L);
        delay(100);
        bleHID.sendKeyboard(Keyboard::NONE, Keyboard::L);
        delay(100);
        bleHID.sendKeyboard(Keyboard::NONE, Keyboard::O);
        delay(1000);
        
        // Move mouse in a square
        bleHID.sendMouse(50, 0, Mouse::NONE);
        delay(100);
        bleHID.sendMouse(0, 50, Mouse::NONE);
        delay(100);
        bleHID.sendMouse(-50, 0, Mouse::NONE);
        delay(100);
        bleHID.sendMouse(0, -50, Mouse::NONE);
        delay(1000);
    }
}