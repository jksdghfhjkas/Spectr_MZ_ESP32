#include "bluetoothManager.h"
#include "wifiCredentials.h"

void BluetoothManager::init() {
    serialBT.begin(name);
}

WiFiCredentials BluetoothManager::get_credentials() {
    WiFiCredentials creds;

    if (!serialBT.available()) {
        return creds;
    }

    String response = serialBT.readString();
    response.trim();

    int first = response.indexOf(' ');
    int second = response.lastIndexOf(' ');
    if (first <= 0 || second <= first) return creds;

    String ssid = response.substring(0, first);
    String password = response.substring(first + 1, second);
    String id = response.substring(second + 1);

    if (ssid.length() == 0 || id.length() == 0) {
        return creds;
    }
    creds.valid = true;
    creds.ssid = ssid;
    creds.password = password;
    creds.id = id;
    return creds;
}

void BluetoothManager::send(String response) {
    if (serialBT.hasClient()) {
        // serialBT.println("Прибор не может подключиться к wifi. \nУбедитесь что вы правильно заполнили параметры сети и сеть имеет частоту 2.4Гц.");
        serialBT.println(response);
    };
}

