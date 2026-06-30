/**
 * ============================================================
 * IoT Energy Monitor
 * ------------------------------------------------------------
 * File        : PowerMonitor.cpp
 * Descrizione : Implementazione della libreria PowerMonitor.
 * Versione    : 1.0.0
 * ============================================================
 */

#include "PowerMonitor.h"

#include <math.h>

//
//--------------------------------------------------------------
// Costruttore
//--------------------------------------------------------------
//

PowerMonitor::PowerMonitor(const MonitorConfig& configuration)
    : _configuration(configuration),
      _offset(0.0f),
      _adcMaxValue(0),
      _adcLsbVoltage(0.0f),
      _calibrationFactor(0.0f),
      _initialized(false)
{
}
//
//--------------------------------------------------------------
// Inizializzazione
//--------------------------------------------------------------
//

bool PowerMonitor::begin()
{
    if (!configurationIsValid())
    {
        return false;
    }

    analogReadResolution(_configuration.adcBits);

    _adcMaxValue = (1U << _configuration.adcBits) - 1U;

    _adcLsbVoltage =
        _configuration.adcReference /
        static_cast<float>(_adcMaxValue);

    updateCalibration();

    _offset = estimateInitialOffset();

    _initialized = true;

    return true;
}

//
//--------------------------------------------------------------
// Aggiornamento configurazione
//--------------------------------------------------------------
//

void PowerMonitor::updateConfiguration(
    const MonitorConfig& configuration)
{
    _configuration = configuration;

    _adcMaxValue =
        (1U << _configuration.adcBits) - 1U;

    _adcLsbVoltage =
        _configuration.adcReference /
        static_cast<float>(_adcMaxValue);

    updateCalibration();
}

//
//--------------------------------------------------------------
// Aggiornamento calibrazione
//--------------------------------------------------------------
//

void PowerMonitor::updateCalibration()
{
    _calibrationFactor =
        _adcLsbVoltage *
        static_cast<float>(_configuration.sensorTurns) /
        _configuration.burden;
}

//
//--------------------------------------------------------------
// Lettura data raw
//--------------------------------------------------------------
//

uint16_t PowerMonitor::readAdc()
{
#if BUILD_TEST_MODE

    static float phase = 0.0f;

    constexpr float amplitude = 300.0f;
    constexpr float offset = 2048.0f;

    phase += 0.08f;

    if (phase > TWO_PI)
    {
        phase -= TWO_PI;
    }

    return static_cast<uint16_t>(
        offset + amplitude * sinf(phase));

#else

    return analogRead(_configuration.analogPin);

#endif
}


void PowerMonitor::updateOffset(uint16_t sample)
{
    _offset += Constants::OffsetFilter *
               (static_cast<float>(sample) - _offset);
}


bool PowerMonitor::configurationIsValid() const
{
    if (_configuration.sensorTurns == 0)
        return false;

    if (_configuration.burden <= 0.0f)
        return false;

    if (_configuration.adcReference <= 0.0f)
        return false;

    if (_configuration.adcBits < 10)
        return false;

    if (_configuration.adcBits > 16)
        return false;

    if (_configuration.samples == 0)
        return false;

    return true;
}


float PowerMonitor::estimateInitialOffset()
{
    constexpr uint16_t InitialSamples = 512;

    uint32_t sum = 0;

    for (uint16_t i = 0; i < InitialSamples; ++i)
    {
        sum += readAdc();
    }

    return static_cast<float>(sum) /
           static_cast<float>(InitialSamples);
}


MeasureResult PowerMonitor::measure(Measurement& measurement)
{
    measurement = {};

    if (!_initialized)
    {
        return MeasureResult::NotInitialized;
    }

    if (!configurationIsValid())
    {
        return MeasureResult::InvalidConfiguration;
    }

    const float measurementOffset = _offset;

    float sumSquaredSamples = 0.0f;

    const uint32_t startTime = micros();

    for (uint16_t i = 0; i < _configuration.samples; ++i)
    {
        const uint16_t adcSample = readAdc();

        updateOffset(adcSample);

        const float filteredSample =
            static_cast<float>(adcSample) - measurementOffset;

        sumSquaredSamples +=
            filteredSample * filteredSample;
    }

    const uint32_t acquisitionTime =
        micros() - startTime;

    const float meanSquare =
        sumSquaredSamples /
        static_cast<float>(_configuration.samples);

    const float rmsAdc = sqrtf(meanSquare);

    measurement.irms =
        rmsAdc * _calibrationFactor;

    measurement.apparentPowerVA =
        measurement.irms *
        _configuration.mainsVoltage;

    measurement.offset = measurementOffset;

    measurement.sampleCount =
        _configuration.samples;

    measurement.acquisitionTime =
        acquisitionTime;

    measurement.valid = true;

    return MeasureResult::Ok;
}


