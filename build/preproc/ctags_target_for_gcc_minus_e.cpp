# 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino"

# 3 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2
# 4 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\TMC2160-SPI-TEST\\TMC2160-SPI-TEST.ino" 2

void setup(){
    HWCDCSerial.begin(115200);
    delay(5000);
    HWCDCSerial.println("TMC2160 SPI Test");
}

void loop(){
    // Main loop code
}
