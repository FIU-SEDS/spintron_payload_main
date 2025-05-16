/**
 * Functions and constants related to checking if the device is currently in apogee
 */

/**
 * Threshold for the IMU to consider the device starting apogee
 */
const double STARTING_IMU_THRESH = 2 * 9.81;

/** Threshold for the IMU to consider the device ending apogee
 * device in apogee
 */
const double ENDING_IMU_THRESH = -0.5;

/**
 * Threshold for the IMU to consider the device starting apogee
 */
const double STARTING_ACC_THRESH = 0.20;

/** Threshold for the IMU to consider the device ending apogee
 * device in apogee
 */
const double ENDING_ACC_THRESH = -0.5;

/**
 * Is the IMU in apogee
 *
 * Returns true of the value from the z value from the IMU
 * is between +- the IMU_Z_THRESH
 */
bool isIMUApogee()
{
  updateIMU();

  float totalAccMag = imuAccelerationMagMovingAvg();

  return totalAccMag < STARTING_IMU_THRESH;
}

/**
 * Is the accelerometer in apogee
 *
 * Returns true of the value from the z value from the accelerometer
 * is between +- the ACCELO_Z_THRESH
 */
bool isAcceloAppoge()
{
  updateAcc();

  float totalAccMag = AccMagMovingAvg();

  return totalAccMag < STARTING_ACC_THRESH;
}

bool isInApogee()
{
  return isIMUApogee();
}
