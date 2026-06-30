#ifndef MODELS_H
#define MODELS_H

/**
 * ============================================================
 * IoT Energy Monitor
 * ------------------------------------------------------------
 * File        : models.h
 * Descrizione : Definizione dei modelli dati condivisi
 * Versione    : 1.0.0
 * ============================================================
 */

#include <Arduino.h>

//
//--------------------------------------------------------------
// Configurazione del monitor
//--------------------------------------------------------------
//

struct MonitorConfig
{
    uint8_t     analogPin;

    uint16_t    sensorTurns;

    float       burden;

    float       mainsVoltage;

    float       adcReference;

    uint16_t    adcResolution;

    uint16_t    samples;

    uint8_t     frequency;

    uint16_t    sampleInterval;
};

//
//--------------------------------------------------------------
// Configurazione rete
//--------------------------------------------------------------
//

struct NetworkConfig
{
    char wifiSSID[33];

    char wifiPassword[65];

    char hostName[32];

    char mdnsName[32];

    char ntpServer[64];

    char mqttServer[64];

    uint16_t mqttPort;

    char mqttProtocol[16];

    char topicStatus[64];

    char topicSave[64];

    char topicCommand[64];
};

//
//--------------------------------------------------------------
// Configurazione storico
//--------------------------------------------------------------
//

struct HistoryConfig
{
    uint16_t saveInterval;

    uint16_t coverageHours;
};

//
//--------------------------------------------------------------
// Configurazione grafica
//--------------------------------------------------------------
//

struct AppearanceConfig
{
    bool darkMode;

    char fontName[32];

    uint8_t fontSize;
};

//
//--------------------------------------------------------------
// Misura
//--------------------------------------------------------------
//

struct Measurement
{
    uint32_t timestamp;

    float irms;

    float power;

    uint16_t samples;

    uint32_t acquisitionTime;

    bool valid;
};

//
//--------------------------------------------------------------
// Stato del monitor
//--------------------------------------------------------------
//

struct MonitorStatus
{
    bool wifiConnected;

    bool mqttConnected;

    bool ntpSynchronized;

    bool webServerRunning;

    bool storageReady;

    float currentIrms;

    float currentPower;

    uint32_t uptime;

    uint32_t freeHeap;

    uint32_t lastMeasurement;
};

//
//--------------------------------------------------------------
// Configurazione completa
//--------------------------------------------------------------
//

struct Configuration
{
    MonitorConfig monitor;

    NetworkConfig network;

    HistoryConfig history;

    AppearanceConfig appearance;
};

//
//--------------------------------------------------------------
// Applicazione completa
//--------------------------------------------------------------
//

struct Application
{
    Configuration config;

    MonitorStatus status;
};

#endif