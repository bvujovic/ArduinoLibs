#ifndef WIFI_SRV_BASICS_H
#define WIFI_SRV_BASICS_H

#if ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
typedef ESP8266WebServer WebServ;
#include <ESP8266mDNS.h>
#include <LittleFS.h>
#else
#include <WiFi.h>
#include <WebServer.h>
typedef WebServer WebServ;
#include <mDNS.h>
#include <SPIFFS.h>
#endif
#include <WiFiClient.h>
//B #include "FS.h"
#include <CredWiFi.h>

// void handleDataFile(WebServ &srv, String path, String mime);
// void connectToWiFi(int ipLastNum);

//* Ucitavanje fajla u string koji se kasnije momentalno (bez citanja fajla) moze vratiti korisniku kao HTTP odgovor
// https://www.arduino.cc/reference/en/language/functions/communication/stream/streamreadbytes/
// https://www.arduino.cc/reference/en/language/functions/communication/stream/streamreadstring/

void HandleDataFile(WebServ &srv, String path, String mime);
void ConnectToWiFi();
void SetupIPAddress(int ipLastNum);
void SendEmptyText(WebServ &srv);

#endif