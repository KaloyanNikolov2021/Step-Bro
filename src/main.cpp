#include <Arduino.h>
#include <Wire.h>
<<<<<<< HEAD
#include <VL53L4CD.h>         // ToF библиотека
#include <SparkFun_BMA400.h>  // BMA400 библиотека

VL53L4CD tofSensor;
BMA400 accel;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Инициализация на ToF
  if (!tofSensor.begin()) {
    Serial.println("ToF sensor not found!");
    while (1);
  }
  tofSensor.startRanging();

  // Инициализация на акселерометъра
  if (!accel.begin()) {
    Serial.println("BMA400 not found!");
    while (1);
  }
  Serial.println("Sensors initialized!");
}

void loop() {
  // ToF измерване
  if (tofSensor.dataReady()) {
    tofSensor.getRangingData();
    Serial.print("ToF Distance (mm): ");
    Serial.println(tofSensor.ranging_data.range_mm);
  }

  // BMA400 ускорение
  accel.readAccel();
  Serial.print("Accel X: "); Serial.print(accel.x);
  Serial.print(" Y: "); Serial.print(accel.y);
  Serial.print(" Z: "); Serial.println(accel.z);

  delay(200); // малка пауза
}

#version 3 
=======
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
>>>>>>> old_history
