#include "Arduino.h"
#include "TMC2160.h"
#include "TMC2160_SPI_Callback.h"

void setup() {

  Serial.begin(115200);

  pinMode(2, OUTPUT); digitalWrite(2, HIGH);  // Enable pin
  pinMode(3, OUTPUT); digitalWrite(3, HIGH); // Step pin
  pinMode(4, OUTPUT); digitalWrite(4, LOW);  // Direction pin

}

void loop(){
    // Example usage of TMC2160 API
    uint16_t icID = 0; // Assuming a single IC for simplicity
    uint8_t address = TMC2160_IOIN___OUTPUT; // Example register address
    int32_t value = tmc2160_readRegister(icID, address);
    
    Serial.print("Read value from register 0x");
    Serial.print(address, HEX);
    Serial.print(": ");
    Serial.println(value, HEX);

    // Write a value to a register
   // tmc2160_writeRegister(icID, address, 0x12345678);
    
    delay(1000); // Delay for demonstration purposes
}
