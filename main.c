#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <memory.h>
#include "hardware/flash.h"
#include "time.h"
#include "hardware/i2c.h"
#include "I2CUtils.h"
#include "ICM46288.h"
#include "LPS25.h"


int main() {
  stdio_init_all();
  while (!stdio_usb_connected()) { //wait while
    sleep_ms(50);
  }
  printf("Started\n");

  setupi2c();
  icm42688Init();
  lps25Init();

  while (true) {
    icm42688Poll();
    lps25Poll();
    icm42688PrintData();
    printf("\t\t");
    lps25Poll();
    printf("\n");

    sleep_ms(5);
//    char c = getchar();
  }
}