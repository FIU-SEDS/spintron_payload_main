#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <queue>
#include <tuple>

const int ACCELEROMETER_SENSOR_ID = 12345;
#define ACC_MOVING_AVG_WINDOW_SIZE 3

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(ACCELEROMETER_SENSOR_ID);


sensors_event_t event;

using DoubleTuple2 = std::tuple<double, double, double>;
std::queue<DoubleTuple2> accDataQueue;

void updateAcc() {
  accel.getEvent(&event);
  accDataQueue.push(std::make_tuple(getXAcc(), getAccY(), getAccZ()));

  if (accDataQueue.size() > ACC_MOVING_AVG_WINDOW_SIZE) {
    accDataQueue.pop();
  }
}

/**
 * Returns the acceleration from the Accelerometer in the X direction
 */
float getXAcc()
{
  return event.acceleration.x;
}

/**
 * Returns the acceleration from the Accelerometer in the Y direction
 */
float getAccY()
{
  return event.acceleration.y;
}

/**
 * Returns the acceleration from Accelerometer in the in the Z direction
 */
float getAccZ()
{
  return event.acceleration.z;
}

/**
 * Calculates the magnitude of the acceleration vector.
 */
float getAccelerationMagnitude() {
  return sqrt(getXAcc() * getXAcc() + getAccY() * getAccY() + getAccZ() * getAccZ());
}

/**
 * Initalized the accelerometer and returns a 0 value if successfull.
 * @return 0 on success, non-zero otherwise.
 */
int setupAccelerometer()
{
  if (!accel.begin())
  {
    return -1;
  }

  accel.setDataRate(ADXL345_DATARATE_3200_HZ);
  accel.setRange(ADXL345_RANGE_16_G);
  return 0;
}

/**
 * Calculates the moving average of the IMU total acceleration magnitude.
 *
 * @return The moving average of the IMU acceleration.
 */
double AccMagMovingAvg() {
  // Calculate the moving average
  if (accDataQueue.empty()) {
    return 0.0;
  }

  double sum = 0.0;

  std::queue<DoubleTuple2> tempQueue = accDataQueue; // Create a copy

  while (!accDataQueue.empty()) {
    DoubleTuple2 value = tempQueue.front(); // Get the front element
    double x = std::get<0>(value);
    double y = std::get<1>(value);
    double z = std::get<2>(value);

    sum += sqrt(x * x + y * y + z * z);

    tempQueue.pop(); // Remove the front element from the copy
  }

  double avg = sum / accDataQueue.size();

  return avg;
}
