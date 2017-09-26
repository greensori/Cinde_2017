
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

void setup() {
    Wire.begin();

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(19200);

    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
  delay(500);
  //accel, gyro, magnetic
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Serial.print("dof10:\t");
    Serial.print("ax_");Serial.print(ax); Serial.print(",");
    Serial.print("ay_");Serial.print(ay); Serial.print(",");
    Serial.print("az_");Serial.print(az); Serial.print(",");
    Serial.print("gx_");Serial.print(gx); Serial.print(",");
    Serial.print("gy_");Serial.print(gy); Serial.print(",");
    Serial.print("gz_");Serial.print(gz); Serial.print(",");
    Serial.print("mx_");Serial.print(mx); Serial.print(",");
    Serial.print("my_");Serial.print(my); Serial.print(",");
    Serial.print("mz_");Serial.print(mz); Serial.print(",");
    Serial.println("end");
}
