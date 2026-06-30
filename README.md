# EnergyMonitor

| Modulo              | Responsabilità                          |
| ------------------- | --------------------------------------- |
| `ESP32EmonLib`      | Acquisizione ADC e calcolo della misura |
| `storage`           | Memorizzazione persistente              |
| `mqtt`              | Comunicazione MQTT                      |
| `webserver`         | Gestione HTTP                           |
| `pages`             | HTML                                    |
| `style`             | CSS                                     |
| `script`            | JavaScript                              |
| `EnergyMonitor.ino` | Coordinamento dell'intera applicazione  |


EnergyMonitor/

├── EnergyMonitor.ino          // Programma principale
│
├── config.h                   // Costanti e valori di default
├── models.h                   // Tutte le strutture dati
├── secret.h                   // Credenziali WiFi
│
├── ESP32EmonLib.h
├── ESP32EmonLib.cpp           // Misura corrente
│
├── storage.h
├── storage.cpp                // Memoria persistente
│
├── mqtt.h
├── mqtt.cpp                   // MQTT
│
├── webserver.h
├── webserver.cpp              // Server HTTP
│
├── pages.h                    // HTML
├── style.h                    // CSS
├── script.h                   // JavaScript
│
└── utilities.h                // Funzioni comuni


measure()

    │
    ├── Verifica inizializzazione
    │
    ├── Verifica configurazione
    │
    ├── Azzera accumulatori
    │
    ├── Acquisisce N campioni ADC
    │       │
    │       ├── readAdc()
    │       ├── updateOffset()
    │       ├── calcola campione filtrato
    │       └── accumula il quadrato
    │
    ├── Calcola Irms
    │
    ├── Calcola Potenza
    │
    ├── Compila Measurement
    │
    └── Restituisce MeasureResult::Ok

    measure()

    │

    ├── validate()

    ├── acquireSamples()

    ├── computeIrms()

    ├── computePower()

    └── fillMeasurement()


Algoritmo PowerMonitor

verifica inizializzazione

↓

verifica configurazione

↓

azzera accumulatori

↓

inizia timer

↓

per ogni campione

    adc = readAdc()

    updateOffset()

    filtered = adc - offset

    sumSquares += filtered²

↓

ferma timer

↓

rmsADC = sqrt(sumSquares / N)

↓

Irms = rmsADC × calibrationFactor

↓

Power = Irms × tensione

↓

riempi Measurement

↓

return Ok


PowerMonitor
│
├── acquireSamples()
│
├── estimateInitialOffset()
│
├── processSamples()
│
├── calculateIrms()
│
└── measure()


| Test                              | Esito |
| --------------------------------- | :---: |
| Compilazione                      |   ☐   |
| Sinusoide simulata                |   ☐   |
| Offset fisso                      |   ☐   |
| Offset variabile                  |   ☐   |
| Rumore ±5 LSB                     |   ☐   |
| Saturazione ADC                   |   ☐   |
| SCT-013-000 a vuoto               |   ☐   |
| Carico resistivo noto             |   ☐   |
| Confronto con pinza amperometrica |   ☐   |


