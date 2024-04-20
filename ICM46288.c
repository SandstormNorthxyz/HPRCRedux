#include "ICM46288.h"

float _t = 0.0f;
float _acc[3] = {};
float _gyr[3] = {};

///\brief Full scale resolution factors
float _accelScale = 1.0f;
float _gyroScale = 1.0f;

///\brief Accel calibration
float _accBD[3] = {};
float _accB[3] = {};
float _accS[3] = {1.0f, 1.0f, 1.0f};
float _accMax[3] = {};
float _accMin[3] = {};

///\brief Gyro calibration
float _gyroBD[3] = {};
float _gyrB[3] = {};

void icm42688Init(){
  writeReg(0x68, 0x11, 0x01); //reset accel
  sleep_ms(1);
  writeReg(0x68, 0x4E, 0x0F); //start accel and gyro
  sleep_ms(1);

  uint8_t gyroReg;
  readReg(0x68, 0x4F, 1, &gyroReg);
  gyroReg = odr200 | (gyroReg & 0xF0);
  gyroReg = (dps2000 << 5) | (gyroReg & 0x1F);
  writeReg(0x68, 0x4F, gyroReg);
  _gyroScale = (2000.0f / (1 << dps2000)) / 32768.0f;

  sleep_ms(1);

  uint8_t accelReg;
  readReg(0x68, 0x50, 1, &accelReg);
  accelReg = odr200 | (accelReg & 0xF0);
  accelReg = (gpm16 << 5) | (accelReg & 0x1F);
  writeReg(0x68, 0x50, accelReg);
  _accelScale = (1 << (4 - gpm16)) / 32768.0f;

  sleep_ms(1);
}

void icm42688Poll(){
  uint8_t readBuf[14] = {0};
  readReg(0x68, 0x1D, 14, readBuf); //read accelerometer

  int16_t rawMeas[7]; // temp, accel xyz, gyro xyz
  for (size_t i=0; i<7; i++) {
    rawMeas[i] = ((int16_t)readBuf[i*2] << 8) | readBuf[i*2+1];
  }

  _acc[0] = ((rawMeas[1] * _accelScale) - _accB[0]) * _accS[0];
  _acc[1] = ((rawMeas[2] * _accelScale) - _accB[1]) * _accS[1];
  _acc[2] = ((rawMeas[3] * _accelScale) - _accB[2]) * _accS[2];

  _gyr[0] = (rawMeas[4] * _gyroScale) - _gyrB[0];
  _gyr[1] = (rawMeas[5] * _gyroScale) - _gyrB[1];
  _gyr[2] = (rawMeas[6] * _gyroScale) - _gyrB[2];
}

void icm42688PrintData(){
  printf("Gyro: %f %f %f\tAccel: %f %f %f", _gyr[0], _gyr[1], _gyr[2], _acc[0], _acc[1], _acc[2]);
}
