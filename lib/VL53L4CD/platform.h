#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <Arduino.h>
#include <Wire.h>

#ifdef __cplusplus
extern "C" {
#endif

int8_t VL53L4CD_ReadMulti(uint16_t dev, uint16_t reg, uint8_t *pdata, uint32_t count);
int8_t VL53L4CD_WriteMulti(uint16_t dev, uint16_t reg, uint8_t *pdata, uint32_t count);
int8_t VL53L4CD_RdByte(uint16_t dev, uint16_t reg, uint8_t *pdata);
int8_t VL53L4CD_WrByte(uint16_t dev, uint16_t reg, uint8_t data);
int8_t VL53L4CD_WaitMs(uint32_t time_ms);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_H_ */
