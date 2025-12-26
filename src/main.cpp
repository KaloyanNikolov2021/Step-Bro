#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cd_class.h>

/* ============================================================
   Константи
   ============================================================ */
#define VL53L4CD_I2C_ADDR  0x52   // 8-bit address (ST style)

/* ============================================================
   Arduino setup / loop
   ============================================================ */

VL53L4CD sensor(&Wire, -1); // No XSHUT pin

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    Serial.println("VL53L4CD boot");

    Wire.begin();
    Wire.setClock(100000);

    sensor.begin();

    /* --- Init sensor --- */
    if (sensor.InitSensor(VL53L4CD_I2C_ADDR) != VL53L4CD_ERROR_NONE) {
        Serial.println("Sensor init FAILED");
        while (1);
    }

    Serial.println("Sensor init OK");

    // Increase timing budget for better accuracy
    sensor.VL53L4CD_SetRangeTiming(200, 0);

    // Calibration sequence
    Serial.println("Starting calibration...");
    Serial.println("Place sensor at 100mm from target.");
    delay(5000); // Give time to position the sensor

    int16_t offset;
    if (sensor.VL53L4CD_CalibrateOffset(100, &offset, 10) == VL53L4CD_ERROR_NONE) {
        Serial.print("Offset calibrated: ");
        Serial.println(offset);
    } else {
        Serial.println("Offset calibration failed");
    }

    uint16_t xtalk;
    if (sensor.VL53L4CD_CalibrateXtalk(100, &xtalk, 10) == VL53L4CD_ERROR_NONE) {
        Serial.print("Xtalk calibrated: ");
        Serial.println(xtalk);
    } else {
        Serial.println("Xtalk calibration failed");
    }

    Serial.println("Calibration done. Starting ranging.");

    sensor.VL53L4CD_StartRanging();
}

void loop()
{
    uint8_t data_ready = 0;
    VL53L4CD_Result_t result;

    sensor.VL53L4CD_CheckForDataReady(&data_ready);
    if (data_ready) {

        sensor.VL53L4CD_GetResult(&result);

        // --- минимална промяна: CSV формат за Python ---
        Serial.print(millis());          // време в ms
        Serial.print(",");
        Serial.print(result.distance_mm); // разстояние
        Serial.print(",");
        Serial.println(result.range_status); // статус

        sensor.VL53L4CD_ClearInterrupt();
    }

    delay(20); // ~50 Hz
}
/* ============================================================
   Край на файла
   ============================================================ */