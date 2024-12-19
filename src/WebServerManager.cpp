#include "WebServerManager.h"

WebServerManager::WebServerManager(const char* ssid, const char* password) 
    : server(80), ssid(ssid), password(password) {}

void WebServerManager::begin() {
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("An error occurred while mounting SPIFFS");
        return;
    }

    // Set up Access Point
    WiFi.softAP(ssid.c_str(), password.c_str());
    
    // Set up routes
    setupRoutes();
    
    // Start server
    server.begin();
    Serial.println("HTTP server started");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
}

void WebServerManager::setupRoutes() {
    server.on("/", HTTP_GET, [this](){ this->handleRoot(); });
    server.on("/upload", HTTP_POST, [](){ server.send(200); }, [this](){ this->handleFileUpload(); });
    server.onNotFound([this](){ this->handleNotFound(); });
}

void WebServerManager::handleClient() {
    server.handleClient();
}

void WebServerManager::handleRoot() {
    if (handleFileRead("/index.html")) {
        return;
    }
    String html = "<html><body>";
    html += "<h1>ESP32 Web Server</h1>";
    html += "<p>Upload files using the form below:</p>";
    html += "<form method='post' action='/upload' enctype='multipart/form-data'>";
    html += "<input type='file' name='file'><input type='submit' value='Upload'>";
    html += "</form></body></html>";
    server.send(200, "text/html", html);
}

void WebServerManager::handleNotFound() {
    if (!handleFileRead(server.uri())) {
        String message = "File Not Found\n\n";
        message += "URI: " + server.uri() + "\n";
        message += "Method: " + String((server.method() == HTTP_GET) ? "GET" : "POST") + "\n";
        server.send(404, "text/plain", message);
    }
}

String WebServerManager::getContentType(String filename) {
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    else if (filename.endsWith(".json")) return "application/json";
    return "text/plain";
}

bool WebServerManager::handleFileRead(String path) {
    if (path.endsWith("/")) path += "index.html";
    String contentType = getContentType(path);
    if (SPIFFS.exists(path)) {
        File file = SPIFFS.open(path, "r");
        server.streamFile(file, contentType);
        file.close();
        return true;
    }
    return false;
}

void WebServerManager::handleFileUpload() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
        String filename = upload.filename;
        if (!filename.startsWith("/")) filename = "/" + filename;
        File file = SPIFFS.open(filename, "w");
        if (!file) {
            Serial.println("Failed to open file for writing");
            return;
        }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
        File file = SPIFFS.open(upload.filename, "a");
        if (file) {
            file.write(upload.buf, upload.currentSize);
            file.close();
        }
    }
}