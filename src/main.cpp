#include <Arduino.h>
#include <Wire.h>
#include "vl53l4cd_class.h"  // Includes the VL53L4CD class
#include "vl53l4cd_api.h"    // Includes API structures like VL53L4CD_Result_t

// Create an instance of the VL53L4CD sensor class
// Constructor: VL53L4CD(TwoWire *i2c, int xshut_pin)
// Use -1 for xshut_pin if not connected (as in your setup)
VL53L4CD sensor(&Wire, -1);

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    // Initialize the sensor with default I2C address (0x52)
    // This calls VL53L4CD_SensorInit internally via the class
    if (sensor.InitSensor() != VL53L4CD_ERROR_NONE) {
        Serial.println("Sensor initialization failed!");
        while (1);  // Halt on error
    }

    // Start ranging
    sensor.VL53L4CD_StartRanging();
}

void loop()
{
    VL53L4CD_Result_t res;
    uint8_t ready = 0;

    // Check if data is ready
    sensor.VL53L4CD_CheckForDataReady(&ready);
    if (ready) {
        // Get the result
        sensor.VL53L4CD_GetResult(&res);

        Serial.print(res.distance_mm);
        Serial.println(" mm");

        // Clear the interrupt
        sensor.VL53L4CD_ClearInterrupt();
    }

    delay(50);
}