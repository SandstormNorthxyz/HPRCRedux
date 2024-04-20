#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "I2CUtils.h"

void setupi2c(){
  i2c_init(i2c_default, 100 * 1000);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
}

void writeReg(uint8_t devAddr, uint8_t regAddr, uint8_t regData){
  uint8_t buf[2] = {regAddr, regData};
  i2c_write_blocking(i2c_default, devAddr, buf, 2, false);
}

void readReg(uint8_t devAddr, uint8_t regAddr, uint8_t len, uint8_t* destBuf){
  uint8_t buf[1] = {regAddr};
  i2c_write_blocking(i2c_default, devAddr, buf, 1, false);
  i2c_read_blocking(i2c_default, devAddr, destBuf, 14, false);
}

void print_buf(const uint8_t *buf, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    printf(" %c ", buf[i]);
    printf(" %i ", buf[i]);
    printf("\n");
  }
}
