#include "WiFiServerBasics.h"

void HandleDataFile(WebServ &srv, String path, String mime)
{
#ifdef __LITTLEFS_H
    File f = LittleFS.open(path, "r");
#else
    File f = SPIFFS.open(path, "r");
#endif
    if (f)
    {
        srv.streamFile(f, mime);
        f.close();
    }
    else
        Serial.println(path + " - error reading file.");
}

void ConnectToWiFi()
{
    Serial.print("\nConnecting to ");
    Serial.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 10)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println();
    //T Serial.print("\nIP address: ");
    //T Serial.println(WiFi.localIP());
}

void SetupIPAddress(int ipLastNum)
{
    // ako je tekuca i trazena IP adresa ista (proveravamo samo poslednji broj), onda nema posla za ovu funkciju
    if (WiFi.localIP()[3] == ipLastNum)
        return;

    if (WiFi.status() == WL_CONNECTED)
    {
        IPAddress ipa(192, 168, 0, ipLastNum);
        IPAddress gateway(192, 168, 0, 254);
        IPAddress subnet(255, 255, 255, 0);
        WiFi.config(ipa, gateway, subnet);
        //T Serial.print("IP address set: ");
        //T Serial.println(WiFi.localIP());
    }
    else
        Serial.println("SetupIPAddress: Error!");
}

void SendEmptyText(WebServ &srv)
{
    srv.send(200, "text/plain", "");
}

// void SendEmptyText(WebServer &srv)
// {
//     srv.send(200, "text/plain", "");
// }

// Primer setup() i loop() funkcija za jedan veb server:

// ESP8266WebServer server(80);
//
// void setup()
// {
//     Serial.begin(115200);
//     ConnectToWiFi();
//     SetupIPAddress(25);
//     server.on("/", []() { HandleDataFile(server, "/index.html", "text/html"); });
//     server.on("/favicon.ico", []() { HandleDataFile(server, "/favicon.ico", "image/x-icon"); });
//     server.on("/inc/script.js", []() { HandleDataFile(server, "/inc/script.js", "text/javascript"); });
//     server.on("/inc/style.css", []() { HandleDataFile(server, "/inc/style.css", "text/css"); });
//     server.on("/dat/stuff.csv", []() { HandleDataFile(server, "/dat/stuff.csv", "text/x-csv"); });
//     server.begin();
//     Serial.println("HTTP server started");
//     SPIFFS.begin();
// }
//
// void loop()
// {
//     server.handleClient();
// }