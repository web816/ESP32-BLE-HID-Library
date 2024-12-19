#include "BLEHIDDevice.h"

class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override {
        // Device connected
        BLEDevice::startAdvertising();
    }

    void onDisconnect(BLEServer* pServer) override {
        // Device disconnected
    }
};

BLEHIDDevice::BLEHIDDevice() : connected(false) {}

void BLEHIDDevice::init(const char* deviceName) {
    // Initialize BLE
    BLEDevice::init(deviceName);
    
    // Create BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());

    // Create HID Service
    pHIDService = pServer->createService(BLEUUID((uint16_t)0x1812));

    // Create HID Information Characteristic
    BLECharacteristic* pHIDInfo = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4A),
        BLECharacteristic::PROPERTY_READ
    );
    uint8_t hidInfo[] = {0x00, 0x01, 0x00, 0x00}; // HID version 1.00
    pHIDInfo->setValue(hidInfo, sizeof(hidInfo));

    // Create HID Control Point Characteristic
    BLECharacteristic* pControlPoint = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4C),
        BLECharacteristic::PROPERTY_WRITE_NR
    );

    // Create Report Map Characteristic
    BLECharacteristic* pReportMap = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4B),
        BLECharacteristic::PROPERTY_READ
    );
    
    // Combine keyboard and mouse report descriptors
    uint8_t reportMap[sizeof(HID_KEYBOARD_REPORT_DESCRIPTOR) + sizeof(HID_MOUSE_REPORT_DESCRIPTOR)];
    memcpy(reportMap, HID_KEYBOARD_REPORT_DESCRIPTOR, sizeof(HID_KEYBOARD_REPORT_DESCRIPTOR));
    memcpy(reportMap + sizeof(HID_KEYBOARD_REPORT_DESCRIPTOR), 
           HID_MOUSE_REPORT_DESCRIPTOR, 
           sizeof(HID_MOUSE_REPORT_DESCRIPTOR));
    pReportMap->setValue(reportMap, sizeof(reportMap));

    // Create Input Report Characteristics
    pKeyboardCharacteristic = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4D),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    pKeyboardCharacteristic->addDescriptor(new BLE2902());

    pMouseCharacteristic = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4D),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    pMouseCharacteristic->addDescriptor(new BLE2902());

    // Start the service
    pHIDService->start();

    // Start advertising
    BLEAdvertising* pAdvertising = pServer->getAdvertising();
    pAdvertising->setAppearance(0x03C0); // Keyboard appearance
    pAdvertising->addServiceUUID(pHIDService->getUUID());
    pAdvertising->start();
}

void BLEHIDDevice::sendKeyboard(uint8_t modifiers, uint8_t keycode) {
    if (!connected) return;
    
    uint8_t report[8] = {0};
    report[0] = modifiers;
    report[2] = keycode;
    pKeyboardCharacteristic->setValue(report, sizeof(report));
    pKeyboardCharacteristic->notify();
}

void BLEHIDDevice::sendMouse(int8_t x, int8_t y, uint8_t buttons, int8_t wheel) {
    if (!connected) return;
    
    uint8_t report[4] = {
        buttons,
        (uint8_t)x,
        (uint8_t)y,
        (uint8_t)wheel
    };
    pMouseCharacteristic->setValue(report, sizeof(report));
    pMouseCharacteristic->notify();
}