#include <Arduino.h>
#include <Wire.h>
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
