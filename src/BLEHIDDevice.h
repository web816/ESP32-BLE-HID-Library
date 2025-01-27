#ifndef BLE_HID_DEVICE_H
#define BLE_HID_DEVICE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// HID Report Descriptors
const uint8_t HID_KEYBOARD_REPORT_DESCRIPTOR[] = {
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x06,  // Usage (Keyboard)
    0xA1, 0x01,  // Collection (Application)
    0x85, 0x01,  // Report ID (1)
    0x05, 0x07,  // Usage Page (Key Codes)
    0x19, 0xE0,  // Usage Minimum (224)
    0x29, 0xE7,  // Usage Maximum (231)
    0x15, 0x00,  // Logical Minimum (0)
    0x25, 0x01,  // Logical Maximum (1)
    0x75, 0x01,  // Report Size (1)
    0x95, 0x08,  // Report Count (8)
    0x81, 0x02,  // Input (Data, Variable, Absolute)
    0x95, 0x01,  // Report Count (1)
    0x75, 0x08,  // Report Size (8)
    0x81, 0x01,  // Input (Constant)
    0x95, 0x06,  // Report Count (6)
    0x75, 0x08,  // Report Size (8)
    0x15, 0x00,  // Logical Minimum (0)
    0x25, 0x65,  // Logical Maximum (101)
    0x05, 0x07,  // Usage Page (Key Codes)
    0x19, 0x00,  // Usage Minimum (0)
    0x29, 0x65,  // Usage Maximum (101)
    0x81, 0x00,  // Input (Data, Array)
    0xC0         // End Collection
};

const uint8_t HID_MOUSE_REPORT_DESCRIPTOR[] = {
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x02,  // Usage (Mouse)
    0xA1, 0x01,  // Collection (Application)
    0x85, 0x02,  // Report ID (2)
    0x09, 0x01,  // Usage (Pointer)
    0xA1, 0x00,  // Collection (Physical)
    0x05, 0x09,  // Usage Page (Button)
    0x19, 0x01,  // Usage Minimum (Button 1)
    0x29, 0x03,  // Usage Maximum (Button 3)
    0x15, 0x00,  // Logical Minimum (0)
    0x25, 0x01,  // Logical Maximum (1)
    0x95, 0x03,  // Report Count (3)
    0x75, 0x01,  // Report Size (1)
    0x81, 0x02,  // Input (Data, Variable, Absolute)
    0x95, 0x01,  // Report Count (1)
    0x75, 0x05,  // Report Size (5)
    0x81, 0x01,  // Input (Constant)
    0x05, 0x01,  // Usage Page (Generic Desktop)
    0x09, 0x30,  // Usage (X)
    0x09, 0x31,  // Usage (Y)
    0x09, 0x38,  // Usage (Wheel)
    0x15, 0x81,  // Logical Minimum (-127)
    0x25, 0x7F,  // Logical Maximum (127)
    0x75, 0x08,  // Report Size (8)
    0x95, 0x03,  // Report Count (3)
    0x81, 0x06,  // Input (Data, Variable, Relative)
    0xC0,        // End Collection
    0xC0         // End Collection
};

class BLEHIDDevice {
private:
    BLEServer* pServer;
    BLEService* pHIDService;
    BLECharacteristic* pKeyboardCharacteristic;
    BLECharacteristic* pMouseCharacteristic;
    bool connected;

public:
    BLEHIDDevice();
    void init(const char* deviceName);
    void sendKeyboard(uint8_t modifiers, uint8_t keycode);
    void sendMouse(int8_t x, int8_t y, uint8_t buttons, int8_t wheel = 0);
    bool isConnected() { return connected; }
};

#endif