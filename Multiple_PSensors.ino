#include <Wire.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>
#include <SparkFun_MicroPressure.h>

QWIICMUX myMux;
MicroPressure pressureSensor;

// Choose which one is the "input" sensor (1-based index)
const int INPUT_SENSOR_INDEX = 1; // 1 = Sensor 1

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize Mux
  if (!myMux.begin()) {
    Serial.println("Qwiic Mux not detected. Check connections.");
    while (1);
  }

  // Check all sensors
  for (int i = 0; i < 3; i++) {
    myMux.setPort(i);
    if (!pressureSensor.begin()) {
      Serial.print("❌ Could not detect Pressure Sensor ");
      Serial.println(i + 1);
    } else {
      Serial.print("✅ Pressure Sensor ");
      Serial.print(i + 1);
      Serial.println(" detected.");
    }
  }

  Serial.println("Setup complete.\n");
}

void loop() {
  for (int i = 0; i < 3; i++) {
    myMux.setPort(i);
    float pressure = pressureSensor.getPressure_PSI();

    Serial.print("Pressure Sensor ");
    Serial.print(i + 1);
    Serial.print(" [");

    if ((i + 1) == INPUT_SENSOR_INDEX) {
      Serial.print("INPUT");
    } else {
      Serial.print("OUTPUT");
    }

    Serial.print("]: ");
    Serial.print(pressure);
    Serial.println(" psi");

    delay(500);
  }

  Serial.println("----------------------------");
  delay(1000); // Wait before next cycle
}
