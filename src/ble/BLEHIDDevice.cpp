#include "BLEHIDDevice.h"

class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override {
        BLEDevice::startAdvertising();
    }

    void onDisconnect(BLEServer* pServer) override {}
};

BLEHIDDevice::BLEHIDDevice() 
    : pServer(nullptr)
    , pHIDService(nullptr)
    , pKeyboardCharacteristic(nullptr)
    , pMouseCharacteristic(nullptr)
    , connected(false)
    , deviceName(nullptr) {}

bool BLEHIDDevice::init(const char* name) {
    if (!name) return false;
    
    deviceName = name;
    BLEDevice::init(name);
    
    pServer = BLEDevice::createServer();
    if (!pServer) return false;
    
    pServer->setCallbacks(new ServerCallbacks());
    
    if (!setupHIDService()) return false;
    if (!setupCharacteristics()) return false;
    
    startAdvertising();
    return true;
}

void BLEHIDDevice::setupHIDService() {
    pHIDService = pServer->createService(BLEUUID((uint16_t)0x1812));
    if (!pHIDService) return false;

    // HID Information Characteristic
    BLECharacteristic* pHIDInfo = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4A),
        BLECharacteristic::PROPERTY_READ
    );
    if (!pHIDInfo) return false;
    
    uint8_t hidInfo[] = {0x00, 0x01, 0x00, 0x00}; // HID version 1.00
    pHIDInfo->setValue(hidInfo, sizeof(hidInfo));

    // Report Map Characteristic
    BLECharacteristic* pReportMap = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4B),
        BLECharacteristic::PROPERTY_READ
    );
    if (!pReportMap) return false;
    
    pReportMap->setValue(HID_REPORT_DESCRIPTOR, sizeof(HID_REPORT_DESCRIPTOR));
    return true;
}

bool BLEHIDDevice::setupCharacteristics() {
    if (!pHIDService) return false;

    // Keyboard Characteristic
    pKeyboardCharacteristic = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4D),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    if (!pKeyboardCharacteristic) return false;
    pKeyboardCharacteristic->addDescriptor(new BLE2902());

    // Mouse Characteristic
    pMouseCharacteristic = pHIDService->createCharacteristic(
        BLEUUID((uint16_t)0x2A4D),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    if (!pMouseCharacteristic) return false;
    pMouseCharacteristic->addDescriptor(new BLE2902());

    pHIDService->start();
    return true;
}

void BLEHIDDevice::startAdvertising() {
    if (!pServer) return;
    
    BLEAdvertising* pAdvertising = pServer->getAdvertising();
    if (!pAdvertising) return;
    
    pAdvertising->setAppearance(0x03C0); // Keyboard appearance
    pAdvertising->addServiceUUID(pHIDService->getUUID());
    pAdvertising->start();
}

bool BLEHIDDevice::sendKeyboard(uint8_t modifiers, uint8_t keycode) {
    if (!connected || !pKeyboardCharacteristic) return false;
    
    uint8_t report[8] = {0};
    report[0] = modifiers;
    report[2] = keycode;
    
    pKeyboardCharacteristic->setValue(report, sizeof(report));
    return pKeyboardCharacteristic->notify();
}

bool BLEHIDDevice::sendMouse(int8_t x, int8_t y, uint8_t buttons, int8_t wheel) {
    if (!connected || !pMouseCharacteristic) return false;
    
    uint8_t report[4] = {
        buttons,
        static_cast<uint8_t>(x),
        static_cast<uint8_t>(y),
        static_cast<uint8_t>(wheel)
    };
    
    pMouseCharacteristic->setValue(report, sizeof(report));
    return pMouseCharacteristic->notify();
}