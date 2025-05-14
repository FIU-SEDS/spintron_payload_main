/**
 * Functions and constants related to checking if the device is currently in apogee
 */

/**
 * Threshold for the IMU to consider the device starting apogee
 */
const double SFLIGHT_IMU_THRESH = 4;

/**
 * Threshold for the IMU to consider the device starting apogee
 */
const double SFLIGHT_ACC_THRESH = 4;
;

/**
 * Is the IMU in apogee
 *
 * Returns true of the value from the z value from the IMU
 * is between +- the IMU_Z_THRESH
 */
bool isIMUInFlight()
{
  updateIMU();

  float totalAccMag = imuAccelerationMagMovingAvg();

  return totalAccMag > SFLIGHT_IMU_THRESH;
}

/**
 * Is the accelerometer in apogee
 *
 * Returns true of the value from the z value from the accelerometer
 * is between +- the ACCELO_Z_THRESH
 */
bool isAcceloInFlight()
{
  updateAcc();

  float totalAccMag = AccMagMovingAvg();

  return totalAccMag > SFLIGHT_ACC_THRESH;
}

bool checkIsInFlight()
{
  return isIMUInFlight() && isAcceloInFlight();
}
