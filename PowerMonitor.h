#ifndef POWER_MONITOR_H
#define POWER_MONITOR_H

/**
 * ============================================================
 * IoT Energy Monitor
 * ------------------------------------------------------------
 * File        : PowerMonitor.h
 * Descrizione : Misura della corrente RMS mediante
 *               trasformatore amperometrico.
 *
 * Versione    : 1.0.0
 * ============================================================
 */

#include <Arduino.h>

#include "types.h"
#include "models.h"
#include "config.h"

/**
 * @class PowerMonitor
 *
 * @brief Acquisizione della corrente RMS e calcolo della
 *        potenza attiva assumendo cosφ = 1.
 *
 * Questa classe è completamente indipendente da:
 *
 * - WiFi
 * - MQTT
 * - Web Server
 * - Storage
 * - NTP
 */
class PowerMonitor
{
public:

    /**
     * Costruttore.
     */
    explicit PowerMonitor(const MonitorConfig& configuration);

    /**
     * Inizializza il monitor.
     */
    bool begin();

    /**
     * Aggiorna la configurazione.
     */
    void updateConfiguration(const MonitorConfig& configuration);

    /**
     * Esegue una misura.
     */
    MeasureResult measure(Measurement& measurement);

private:

    /**
     * Legge un campione ADC.
     */
    uint16_t readAdc();

    /**
     * Aggiorna il filtro dell'offset.
     */
    void updateOffset(uint16_t sample);

    /**
     * Calcola la corrente RMS.
     */
    float calculateIrms();

    /**
     * Aggiorna il fattore di calibrazione.
     */
    void updateCalibration();

    /**
     * Verifica la configurazione.
     */
    bool configurationIsValid() const;

private:

    MonitorConfig _configuration;

    float _offset;

    float _calibrationFactor;

    bool _initialized;
};

#endif