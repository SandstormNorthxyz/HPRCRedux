#include "LPS25.h"

float _baroPressure = 0;

void lps25Init(){
  writeReg(0x5C, 0x20, 0b11000000); //CTRL_REG1, so turn on and set 25Hz ODR

  uint8_t reg;
  readReg(0x5C, 0x10, 1, &reg); //RES_CONF, set pressure to 512 internal averages
  reg = reg | 0b00000011;
  writeReg(0x5C, 0x10, reg);
}

void lps25Poll(){
  uint8_t readBuf[3] = {0};
  readReg(0x5C, 0x80 + 0x28, 3, readBuf);

  int32_t raw_pressure;
  raw_pressure = (int32_t)readBuf[2];
  raw_pressure <<= 8;
  raw_pressure |= (int32_t)(readBuf[1]);
  raw_pressure <<= 8;
  raw_pressure |= (int32_t)(readBuf[0]);

  if (raw_pressure & 0x800000) {
    raw_pressure = raw_pressure - 0xFFFFFF;
  }
  _baroPressure = raw_pressure / 4096.0;
}

void lps25PrintData(){
  printf("Pressure: %f", _baroPressure);
}
