#ifndef TYPES_H
#define TYPES_H

/**
 * ============================================================
 * IoT Energy Monitor
 * ------------------------------------------------------------
 * File        : types.h
 * Descrizione : Tipi enumerati condivisi.
 * Versione    : 1.0.0
 * ============================================================
 */

#include <Arduino.h>

/**
 * Esito di una misura.
 */
enum class MeasureResult : uint8_t
{
    Ok = 0,

    NotInitialized,

    InvalidConfiguration,

    InvalidSamples,

    AdcError,

    Overflow
};

/**
 * Stato della connessione WiFi.
 */
enum class WifiStatus : uint8_t
{
    Disconnected = 0,

    Connecting,

    Connected
};

/**
 * Stato della connessione MQTT.
 */
enum class MqttStatus : uint8_t
{
    Disconnected = 0,

    Connecting,

    Connected
};

/**
 * Stato della sincronizzazione NTP.
 */
enum class NtpStatus : uint8_t
{
    NotSynchronized = 0,

    Synchronizing,

    Synchronized
};

/**
 * Tema grafico.
 */
enum class Theme : uint8_t
{
    Dark = 0,

    Light
};

#endif