# 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino"
# 2 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2
# 3 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2
# 4 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2

void setup() {

  HWCDCSerial.begin(115200);

}

// void loop(){

//     uint8_t data[5] = {0x01, 0x87, 0x65, 0x43, 0x21};
//     tmc2160_readWriteSPI(0, &data[0], sizeof(data));
//     Serial.print("SPI Address: ");
//     Serial.print(data[0], HEX);
//     Serial.print(" SPI Data: ");
//     Serial.println((int32_t)data[1] << 24 | (int32_t)data[2] << 16 | (int32_t)data[3] << 8 | (int32_t)data[4], HEX);
//     delay(1000);
// }

void loop(){
    // Example usage of TMC2160 API
    uint16_t icID = 0; // Assuming a single IC for simplicity
    uint8_t address = 0x6F; // Example register address
    int32_t value = tmc2160_readRegister(icID, address);

    HWCDCSerial.print("Read value from register 0x");
    HWCDCSerial.print(address, 16);
    HWCDCSerial.print(": ");
    HWCDCSerial.println(value, 16);

    // Write a value to a register
   // tmc2160_writeRegister(icID, address, 0x12345678);

    delay(1000); // Delay for demonstration purposes
}
