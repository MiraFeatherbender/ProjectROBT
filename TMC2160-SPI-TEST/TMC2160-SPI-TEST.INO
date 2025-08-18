
#include "TMC2160.h"
#include "TMC2160_SPI_Callback.h"

void setup(){
    Serial.begin(115200);
    pinMode(0, OUTPUT);
    digitalWrite(0, LOW);
}

void loop(){
    // Example usage of TMC2160 API
    uint16_t icID = 0; // Assuming a single IC for simplicity
    uint8_t address = 0x6F; // Example register address
    int32_t value = tmc2160_readRegister(icID, address);
    
    Serial.print("Read value from register 0x");
    Serial.print(address, HEX);
    Serial.print(": ");
    Serial.println(value, HEX);

    // // Write a value to a register
    // tmc2160_writeRegister(icID, address, 0x12345678);
    
    delay(1000); // Delay for demonstration purposes
}
