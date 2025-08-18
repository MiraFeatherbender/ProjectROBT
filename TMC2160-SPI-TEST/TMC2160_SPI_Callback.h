#ifndef TMC2160_SPI_CALLBACK_H_
#define TMC2160_SPI_CALLBACK_H_

#include <stdint.h>
#include <stddef.h>
#include "SPI.h"

// Placeholder macros for custom SPI pin assignment
#define TMC2160_SPI_MOSI_PIN   8
#define TMC2160_SPI_MISO_PIN   5
#define TMC2160_SPI_SCK_PIN    7
#define TMC2160_SPI_CS_PIN     6


// SPI status bits struct (bits 39-32)
// typedef struct {
// 	bool resetFlag;      // Bit 0: GSTAT[0]
// 	bool driverError;    // Bit 1: GSTAT[1]
// 	bool sg2;            // Bit 2: DRV_STATUS[24]
// 	bool standstill;     // Bit 3: DRV_STATUS[31]
// 	uint8_t unused;      // Bits 4-7
// 	uint8_t raw;         // Raw status byte
// } TMC2160_SPIStatus;

// Callback returns status bits from last SPI response
extern void tmc2160_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);

#endif // TMC2160_SPI_CALLBACK_H_
