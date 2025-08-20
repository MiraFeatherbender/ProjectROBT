# 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino"
# 2 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2
# 3 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2
# 4 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2

void setup() {

  HWCDCSerial.begin(115200);

  pinMode(2, 0x03); digitalWrite(2, 0x1); // Enable pin
  pinMode(3, 0x03); digitalWrite(3, 0x1); // Step pin
  pinMode(4, 0x03); digitalWrite(4, 0x0); // Direction pin

}

void loop(){
    // Example usage of TMC2160 API
    uint16_t icID = 0; // Assuming a single IC for simplicity
    uint8_t address = 0x04; // Example register address
    int32_t value = tmc2160_readRegister(icID, address);

    HWCDCSerial.print("Read value from register 0x");
    HWCDCSerial.print(address, 16);
    HWCDCSerial.print(": ");
    HWCDCSerial.println(value, 16);

    // Write a value to a register
   // tmc2160_writeRegister(icID, address, 0x12345678);

    delay(1000); // Delay for demonstration purposes
}
