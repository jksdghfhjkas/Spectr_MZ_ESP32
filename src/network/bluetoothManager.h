#include <BluetoothSerial.h>
#include <Arduino.h>

#include "wifiCredentials.h"

class BluetoothManager {
    private:
        String name = "Spectr-MZ";
        BluetoothSerial serialBT;

    public:
        void init();

        // получение данных от пользователя
        WiFiCredentials get_credentials();
        void send(String response);
};