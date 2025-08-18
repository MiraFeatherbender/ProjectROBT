
#include "TMC2160.h"
#include "TMC2160_SPI_Callback.h"

void setup(){
    Serial.begin(115200);
    delay(5000);
    Serial.println("TMC2160 SPI Test");
}

void loop(){
    // Main loop code
}
