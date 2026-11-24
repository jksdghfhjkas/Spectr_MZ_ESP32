#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>

#include "wifiCredentials.h"



class WiFiManager {
    private:


        // параметры сети
        WiFiCredentials data;
        Preferences prefs;
    
    public:
        void init();
        void save_prefs(const WiFiCredentials& c);
        bool is_prefs();
        bool load_prefs();


        bool connect();
};