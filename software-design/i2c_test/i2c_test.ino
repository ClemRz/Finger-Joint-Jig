#include <Wire.h>                   // https://github.com/esp8266/Arduino/
#include "register.h"               // https://github.com/ClemRz/Introduction-to-IoT#use-structures

// i2c settings
#define SLAVE_I2C_ADDRESS   0x09

Register _register;

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  randomSeed(analogRead(0));
  initI2c();
  writeArduino();
}

void loop(void) {
}

void defaultRegister(void) {
  _register.kerfMm = random(0, 1000)/100.0;
  _register.fingerMm = 13.0;
  _register.toleranceUm = 150.0;
  _register.offsetMm = 0.0;
  Serial.println(_register.kerfMm);
}

void initI2c(void) {
  Wire.begin();
}

void writeArduino(void) {
  defaultRegister();
  Wire.beginTransmission(SLAVE_I2C_ADDRESS);
  Wire.write(_register.byteAt, REG_MAP_SIZE);
  Wire.endTransmission();
}
