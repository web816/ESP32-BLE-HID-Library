#include "DNSServerManager.h"

DNSServerManager::DNSServerManager() {}

void DNSServerManager::begin(const IPAddress& localIP) {
    // Configure DNS Server
    dnsServer.start(DNS_PORT, "*", localIP);
    Serial.println("DNS Server started");
}

void DNSServerManager::processNextRequest() {
    dnsServer.processNextRequest();
}

void DNSServerManager::stop() {
    dnsServer.stop();
}