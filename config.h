##ifndef CONFIG_H
#define CONFIG_H

/**
 * ============================================================
 * IoT Energy Monitor
 * ------------------------------------------------------------
 * File        : config.h
 * Descrizione : Costanti di configurazione del progetto.
 * Versione    : 1.0.0
 * ============================================================
 */

#include <Arduino.h>

namespace Firmware
{
    constexpr char Name[] = "IoT Energy Monitor";

    constexpr char Version[] = "1.0.0";
}

namespace Defaults
{
    namespace Monitor
    {
        constexpr uint8_t AnalogPin = 33;

        constexpr uint16_t SensorTurns = 2000;

        constexpr float Burden = 33.0f;

        constexpr float MainsVoltage = 230.0f;

        constexpr float AdcReference = 3.3f;

        constexpr uint16_t AdcResolution = 4095;

        constexpr uint16_t Samples = 1440;

        constexpr uint8_t Frequency = 50;

        constexpr uint16_t SampleInterval = 10;
    }

    namespace History
    {
        constexpr uint16_t SaveInterval = 10;

        constexpr uint16_t CoverageHours = 24;
    }

    namespace Network
    {
        constexpr char HostName[] = "EnergyMonitor";

        constexpr char MdnsName[] = "EnergyMonitor.local";

        constexpr char NtpServer[] = "pool.ntp.org";

        constexpr char MqttServer[] = "broker-cn.emqx.io";

        constexpr uint16_t MqttPort = 1883;

        constexpr char MqttProtocol[] = "MQTT/TCP";

        constexpr char TopicStatus[] = "Riborgo/IOT/Emon/status";

        constexpr char TopicSave[] = "Riborgo/IOT/Emon/save";

        constexpr char TopicCommand[] = "Riborgo/IOT/Emon/command";
    }

    namespace Appearance
    {
        constexpr bool DarkMode = true;

        constexpr char FontName[] = "Arial";

        constexpr uint8_t FontSize = 18;
    }
}

namespace Limits
{
    namespace Monitor
    {
        constexpr uint8_t AnalogPinMin = 32;
        constexpr uint8_t AnalogPinMax = 39;

        constexpr uint16_t SensorTurnsMin = 100;
        constexpr uint16_t SensorTurnsMax = 5000;

        constexpr float BurdenMin = 1.0f;
        constexpr float BurdenMax = 100.0f;

        constexpr float VoltageMin = 100.0f;
        constexpr float VoltageMax = 260.0f;

        constexpr uint16_t SamplesMin = 100;
        constexpr uint16_t SamplesMax = 10000;

        constexpr uint16_t SampleIntervalMin = 1;
        constexpr uint16_t SampleIntervalMax = 3600;
    }

    namespace History
    {
        constexpr uint16_t SaveIntervalMin = 1;
        constexpr uint16_t SaveIntervalMax = 60;

        constexpr uint16_t CoverageMin = 1;
        constexpr uint16_t CoverageMax = 168;
    }
}

namespace Constants
{
    constexpr float OffsetFilter = 1.0f / 1024.0f;
}

#endif