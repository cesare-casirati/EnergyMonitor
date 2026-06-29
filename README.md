# EnergyMonitor

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