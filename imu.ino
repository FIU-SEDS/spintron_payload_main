#include <Adafruit_MPU6050.h>
#include <queue>
#include <tuple>

#define IMU_ACC_RANGE MPU6050_RANGE_8_G
#define IMU_GYRO_RANGE MPU6050_RANGE_500_DEG
#define IMU_REFRESH_RATE MPU6050_BAND_21_HZ

#define IMU_MOVING_AVG_WINDOW_SIZE 3

using DoubleTuple = std::tuple<double, double, double>;
std::queue<DoubleTuple> imuDataQueue;

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

void updateIMU() {
  mpu.getEvent(&a, &g, &temp);

  // Store the IMU data in a queue
  imuDataQueue.push(std::make_tuple(getIMUXAcc(), getIMUYAcc(), getIMUZAcc()));

  if (imuDataQueue.size() > IMU_MOVING_AVG_WINDOW_SIZE) {
    imuDataQueue.pop();
  }
}

/**
 *  Returns the acceleration from the IMU in the X direction.
 */
double getIMUXAcc()
{
  return a.acceleration.x; // Preserve precision
}

/**
 * Returns the acceleration from the IMU in the Y direction.
 */
double getIMUYAcc()
{
  return a.acceleration.y * 100;
}

/**
 * Returns the acceleration from the IMU in the Z direction.
 */
double getIMUZAcc()
{
  return a.acceleration.z;
}

/**
 * Returns the gyroscope value from the IMU in the X direction.
 */
double getIMUXGyro()
{
  return g.gyro.x;
}

/**
 * Returns the gyroscope value from the IMU in the Y direction.
 */
double getIMUYGyro()
{
  return g.gyro.y;
}

/**
 * Returns the gyroscope value from the IMU in the Z direction.
 */
double getIMUZGyro()
{
  return g.gyro.z;
}

/**
 * Returns the temperature from the IMU in Celsius.
 */
double getIMUZTemp()
{
  return temp.temperature;
}

/**
 * Initalized the IMU and returns a 0 value if successfull.
 * @return 0 on success, non-zero otherwise.
 */
int setupIMU()
{
  if (!mpu.begin()) return -1;

  mpu.setAccelerometerRange(IMU_ACC_RANGE);
  mpu.setGyroRange(IMU_GYRO_RANGE);
  mpu.setFilterBandwidth(IMU_REFRESH_RATE);

  return 0;
}

/**
 * Calculates the magnitude of the acceleration vector.
 *
 * @return The magnitude of the acceleration vector.
 */
float getIMUAccelerationMagnitude()
{
  int x = getIMUXAcc();
  int y = getIMUYAcc();
  int z = getIMUZAcc();

  // Calculate the magnitude using the Pythagorean theorem: sqrt(x^2 + y^2 + z^2)
  return sqrt(x * x + y * y + z * z);
}


/**
 * Calculates the moving average of the IMU total acceleration magnitude.
 *
 * @return The moving average of the IMU acceleration.
 */
double imuAccelerationMagMovingAvg() {
  // Calculate the moving average
  if (imuDataQueue.empty()) {
    return 0.0;
  }

  double sum = 0.0;

  std::queue<DoubleTuple> tempQueue = accDataQueue; // Create a copy

  while (!accDataQueue.empty()) {
    DoubleTuple value = tempQueue.front(); // Get the front element
    double x = std::get<0>(value);
    double y = std::get<1>(value);
    double z = std::get<2>(value);

    sum += sqrt(x * x + y * y + z * z);

    tempQueue.pop(); // Remove the front element from the copy
  }

  double avg = sum / imuDataQueue.size();

  return avg;
}
