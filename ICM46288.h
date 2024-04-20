#pragma once
#include "pico/stdlib.h"
#include "I2CUtils.h"


enum ODR : uint8_t {
  odr32k = 0x01, // LN mode only
  odr16k = 0x02, // LN mode only
  odr8k = 0x03, // LN mode only
  odr4k = 0x04, // LN mode only
  odr2k = 0x05, // LN mode only
  odr1k = 0x06, // LN mode only
  odr200 = 0x07,
  odr100 = 0x08,
  odr50 = 0x09,
  odr25 = 0x0A,
  odr12_5 = 0x0B,
  odr6a25 = 0x0C, // LP mode only (accel only)
  odr3a125 = 0x0D, // LP mode only (accel only)
  odr1a5625 = 0x0E, // LP mode only (accel only)
  odr500 = 0x0F,
};

enum GyroFS : uint8_t {
  dps2000 = 0x00,
  dps1000 = 0x01,
  dps500 = 0x02,
  dps250 = 0x03,
  dps125 = 0x04,
  dps62_5 = 0x05,
  dps31_25 = 0x06,
  dps15_625 = 0x07
};

enum AccelFS : uint8_t {
  gpm16 = 0x00,
  gpm8 = 0x01,
  gpm4 = 0x02,
  gpm2 = 0x03
};

void icm42688Init();
void icm42688Poll();
void icm42688PrintData();