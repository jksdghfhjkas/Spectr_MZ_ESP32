#pragma once
#include <Arduino.h>


namespace Config {
    constexpr float ADC_RANGE = 5.0f;
    constexpr float ADC_MAX = 32768.0f;
    constexpr float VOLTS_PER_LSB = ADC_RANGE / ADC_MAX;
    constexpr float AMPS_PER_VOLT = 5.0f;

    // параметры измерения
    constexpr uint32_t SAMPLE_PERIOD_US = 500;   // 2 кГц
    constexpr uint16_t N_SAMPLES        = 400;
}