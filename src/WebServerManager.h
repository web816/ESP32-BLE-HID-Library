#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

#include <WebServer.h>
#include <SPIFFS.h>

class WebServerManager {
private:
    WebServer server;
    String ssid;
    String password;

public:
    WebServerManager(const char* ssid = "ESP32-AP", const char* password = "12345678");
    void begin();
    void handleClient();
    
    // Route handlers
    void setupRoutes();
    void handleRoot();
    void handleNotFound();
    void handleFileUpload();
    
    // Utility functions
    String getContentType(String filename);
    bool handleFileRead(String path);
};

#endif