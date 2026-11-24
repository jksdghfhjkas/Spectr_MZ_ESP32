#pragma once

#include <Arduino.h>

struct WiFiCredentials {
    bool valid = false; // получили данные
    String ssid; // название wifi 
    String password; // пароль
    String id; // id аккаунта
};