#include "vl53l4cd_class.h"
#include "vl53l4cd_api.h"
#include "platform.h"

VL53L4CD::VL53L4CD(uint16_t address)
{
    dev = address;
}

uint8_t VL53L4CD::begin()
{
    return VL53L4CD_SensorInit(dev);
}

uint8_t VL53L4CD::startRanging()
{
    return VL53L4CD_StartRanging(dev);
}

uint8_t VL53L4CD::stopRanging()
{
    return VL53L4CD_StopRanging(dev);
}

uint8_t VL53L4CD::dataReady()
{
    uint8_t ready;
    VL53L4CD_CheckForDataReady(dev, &ready);
    return ready;
}

uint8_t VL53L4CD::getResult(VL53L4CD_Result_t *result)
{
    return VL53L4CD_GetResult(dev, result);
}

uint8_t VL53L4CD::clearInterrupt()
{
    return VL53L4CD_ClearInterrupt(dev);
}
uint8_t VL53L4CD::setDistanceMode(VL53L4CD_DistanceMode_t mode)
{
    return VL53L4CD_SetDistanceMode(dev, mode);
}