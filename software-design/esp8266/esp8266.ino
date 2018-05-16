/**
Copyright (c) 2018, Clément Ronzon
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of current-data-logger nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <Wire.h>                   // https://github.com/esp8266/Arduino/
#include <ESP8266WiFi.h>            // https://github.com/esp8266/Arduino/
#include <WiFiClient.h>             // https://github.com/esp8266/Arduino/
#include <ESP8266WebServer.h>       // https://github.com/esp8266/Arduino/
#include "FS.h"                     // https://github.com/esp8266/Arduino/
#include <ArduinoJson.h>            // https://github.com/bblanchon/ArduinoJson
#include "register.h"               // https://github.com/ClemRz/Introduction-to-IoT#use-structures

// pins
// By default SDA is PIN_WIRE_SDA (4)
// By default SCL is PIN_WIRE_SCL (5)

// FS
#define CONFIG_FILE_PATH    "/cfg.json"

// i2c settings
#define SLAVE_I2C_ADDRESS   0x09

const char *_SSID =         "WiFingerJointJig";

Register _register;
ESP8266WebServer _server(80);

void setup(void) {
  initFS();
  initI2c();
  startAP();
  writeArduino(); //TODO check the timing, it may need a delay (Arduino needs to be ready to receive I2C events)
}

void loop(void) {
  _server.handleClient();
}

void defaultRegister(void) {
  _register.kerfMm = 2.5;
  _register.fingerMm = 13.0;
  _register.toleranceUm = 150.0;
  _register.offsetMm = 0.0;
}
