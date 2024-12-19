#ifndef BLE_HID_DEVICE_H
#define BLE_HID_DEVICE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "../utils/HIDReportDescriptors.h"

class BLEHIDDevice {
private:
    BLEServer* pServer;
    BLEService* pHIDService;
    BLECharacteristic* pKeyboardCharacteristic;
    BLECharacteristic* pMouseCharacteristic;
    bool connected;
    const char* deviceName;

    void setupHIDService();
    void setupCharacteristics();
    void startAdvertising();

public:
    BLEHIDDevice();
    bool init(const char* deviceName);
    bool sendKeyboard(uint8_t modifiers, uint8_t keycode);
    bool sendMouse(int8_t x, int8_t y, uint8_t buttons, int8_t wheel = 0);
    bool isConnected() const { return connected; }
    const char* getDeviceName() const { return deviceName; }
};

#endif