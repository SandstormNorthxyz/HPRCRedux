#pragma once

void setupi2c();

void writeReg(uint8_t devAddr, uint8_t regAddr, uint8_t regData);

void readReg(uint8_t devAddr, uint8_t regAddr, uint8_t len, uint8_t* destBuf);

void print_buf(const uint8_t *buf, size_t len);
