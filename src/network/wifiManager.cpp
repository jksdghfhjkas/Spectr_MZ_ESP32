#include <Preferences.h>
#include <WiFi.h>

#include "wifiManager.h"
#include "wifiCredentials.h"

void WiFiManager::save_prefs(const WiFiCredentials& c) {
    prefs.begin("wifi", false);
    prefs.putString("ssid", c.ssid);
    prefs.putString("password", c.password);
    prefs.putString("id", c.id);
    prefs.end();
    data = c;
}

bool WiFiManager::load_prefs() {
    if (!prefs.begin("wifi", true)) return false;

    data.ssid = prefs.getString("ssid", "");
    data.password = prefs.getString("password", "");
    data.id = prefs.getString("id", "");
    prefs.end();

    data.valid = (data.ssid.length() > 0 && data.id.length() > 0);
    return data.valid;
}

bool WiFiManager::is_prefs() {
    if (!prefs.begin("wifi", true)) return false;
    bool ok = prefs.isKey("ssid") && prefs.isKey("id");
    prefs.end();
    return ok;
}

bool WiFiManager::connect() {
    WiFi.begin(
        data.ssid.c_str(),
        data.password.c_str()
    );

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }

    return false;
}