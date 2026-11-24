#include <Arduino.h>

#include "acp.h"

bool ACP::init() {
    pinMode(PIN_CONVST, OUTPUT);
    pinMode(PIN_BUSY,   INPUT);
    pinMode(PIN_CS,     OUTPUT);
    pinMode(PIN_SCLK,   OUTPUT);
    pinMode(PIN_DOUT,   INPUT);
    pinMode(PIN_RESET,  OUTPUT);

    digitalWrite(PIN_CONVST, HIGH);
    digitalWrite(PIN_CS,     HIGH);
    digitalWrite(PIN_SCLK,   HIGH);
    digitalWrite(PIN_RESET,  LOW);

    resetAD7606();
    if (digitalRead(PIN_BUSY)) {
        return true;
    } else return false;
}

void ACP::resetAD7606() {
    digitalWrite(PIN_RESET, LOW);
    delay(1);
    digitalWrite(PIN_RESET, HIGH);       // импульс сброса
    delayMicroseconds(10);
    digitalWrite(PIN_RESET, LOW);        // дальше RESET остаётся LOW
    delay(2);
}

bool ACP::convertAD7606() {
    digitalWrite(PIN_CONVST, LOW);
    delayMicroseconds(1);
    digitalWrite(PIN_CONVST, HIGH);      // фронт вверх запускает преобразование

    uint32_t t = micros();
    // ждём, пока BUSY упадёт в LOW (по таймауту выходим)
    while (digitalRead(PIN_BUSY) == HIGH) {
        if (micros() - t > 1000) return false;
    }
    return true;
}

int16_t ACP::readChannels() {
    uint16_t value = 0;

    digitalWrite(PIN_SCLK, HIGH);
    digitalWrite(PIN_CS, LOW);
    delayMicroseconds(1);

    value = digitalRead(PIN_DOUT);

    for (int i = 0; i < 15; i++) {
        digitalWrite(PIN_SCLK, LOW);
        delayMicroseconds(1);
        value = (value << 1) | digitalRead(PIN_DOUT);
        digitalWrite(PIN_SCLK, HIGH);
        delayMicroseconds(1);
    }

    digitalWrite(PIN_CS, HIGH);  
    return (int16_t)value;
}

void ACP::loop() {
    static uint32_t next = micros();

    while ((uint32_t)(micros() - next) < 0) { }
    next += Config::SAMPLE_PERIOD_US;

    if (!convertAD7606()) {
        Serial.println("ERR");
        delay(100);
        next = micros();
        return;
    }

    Serial.println(readChannels());
}