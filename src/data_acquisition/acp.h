#include <Arduino.h>

#include "config.h"


#define PIN_CONVST 17   // CONVST A и CONVST B соединить вместе
#define PIN_BUSY   16
#define PIN_CS     5
#define PIN_SCLK   18
#define PIN_DOUT   19   // DOUTA
#define PIN_RESET  23


class ACP {
    private:
        void resetAD7606();
        bool convertAD7606();
        int16_t readChannels();

    public:
        bool init();
        void loop();
};