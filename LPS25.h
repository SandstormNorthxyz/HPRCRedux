#pragma once
#include "pico/stdlib.h"
#include "I2CUtils.h"

void lps25Init();
void lps25Poll();
void lps25PrintData();