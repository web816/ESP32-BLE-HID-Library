#ifndef DNS_SERVER_MANAGER_H
#define DNS_SERVER_MANAGER_H

#include <DNSServer.h>

class DNSServerManager {
private:
    DNSServer dnsServer;
    const byte DNS_PORT = 53;
    
public:
    DNSServerManager();
    void begin(const IPAddress& localIP);
    void processNextRequest();
    void stop();
};

#endif