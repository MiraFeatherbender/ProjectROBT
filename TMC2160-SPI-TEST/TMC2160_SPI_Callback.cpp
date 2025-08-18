#include "TMC2160_SPI_Callback.h"

// SPIClass instance for TMC2160
static SPIClass TMC2160_SPI(HSPI);

// Helper: Set up SPI pins and begin SPI
static void TMC2160_SPI_init()
{
    TMC2160_SPI.begin(TMC2160_SPI_SCK_PIN, TMC2160_SPI_MISO_PIN, TMC2160_SPI_MOSI_PIN, TMC2160_SPI_CS_PIN);
}


// SPI callback implementation
extern "C" void tmc2160_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength)
{
    static bool spi_initialized = false;
    if (!spi_initialized) {
        TMC2160_SPI_init();
        spi_initialized = true;
    }

    // Determine if this is a read or write by checking MSB of address byte
    bool isWrite = (data[0] & 0x80) != 0;

    // Copy outgoing data for debug printing
    uint8_t tx[dataLength];
    for (size_t i = 0; i < dataLength; ++i) {
        tx[i] = data[i];
    }

    digitalWrite(TMC2160_SPI_CS_PIN, LOW);

    // Receive buffer for response
    uint8_t rx[dataLength];
    for (size_t i = 0; i < dataLength; ++i) {
        rx[i] = TMC2160_SPI.transfer(tx[i]);
        data[i] = rx[i]; // Overwrite with received byte for API compatibility
    }

    digitalWrite(TMC2160_SPI_CS_PIN, HIGH);

    // Print debug info to serial
    Serial.print(isWrite ? "Write " : "Read ");
    Serial.print("Addr: 0x"); Serial.print(tx[0], HEX); Serial.print("  Out: ");
    for (size_t i = 1; i < dataLength; ++i) {
        Serial.print(tx[i], HEX); Serial.print(" ");
    }
    Serial.print("  Resp: ");
    for (size_t i = 0; i < dataLength; ++i) {
        Serial.print(rx[i], HEX); Serial.print(" ");
    }
    Serial.println();

    // Parse status bits from first received byte (bits 39-32)
    // TMC2160_SPIStatus status;
    // status.raw = rx[0];
    // status.resetFlag   = (rx[0] & 0x01) != 0;
    // status.driverError = (rx[0] & 0x02) != 0;
    // status.sg2         = (rx[0] & 0x04) != 0;
    // status.standstill  = (rx[0] & 0x08) != 0;
    // status.unused      = (rx[0] >> 4) & 0x0F;

}
