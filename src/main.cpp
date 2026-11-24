#include <Arduino.h>

#include "network/bluetoothManager.h"
#include "network/wifiManager.h"
#include "network/wifiCredentials.h"


BluetoothManager bt;
WiFiManager wifi;



void setup() {
    Serial.begin(921600);
    delay(500);

    bt.init();
    bool has_creds = wifi.load_prefs();

    while (true) {
        if (!has_creds) {
            WiFiCredentials c = bt.get_credentials();
            if (!c.valid) {
                delay(50);
                continue;
            }
            wifi.save_prefs(c);      
            has_creds = true;
        }

        if (wifi.connect()) {
            bt.send("Успешно");
			break;
        }

        bt.send("WIFI_FAIL");      
        has_creds = false;
    }
}

void loop() {

}
