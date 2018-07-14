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
#include <AccelStepper.h>           // http://www.airspayce.com/mikem/arduino/AccelStepper/index.html
#include <LinkedList.h>             // https://github.com/ivanseidel/LinkedList
#include "register.h"               // https://github.com/ClemRz/Introduction-to-IoT#use-structures

// Stepper settings
#define RANGE_IN_MM         307.0                         // mm
#define RANGE_IN_STEPS      14757.0                       // steps
#define STEPS_PER_MM        (RANGE_IN_STEPS/RANGE_IN_MM)  // setps/mm (51.779 steps/mm)
#define MM_PER_STEP         (RANGE_IN_MM/RANGE_IN_STEPS)  // mm/step (0.019 mm/step)
#define FULL_SPEED          1800                          // steps/s (34.763 mm/s)
#define LOW_SPEED           150                           // steps/s (2.897 mm/s)
#define FULL_ACC            4000                          // steps/s2 (77.251 mm/s2)
#define LOW_ACC             200                           // steps/s2 (3.863 mm/s2)

// i2c settings
#define SLAVE_I2C_ADDRESS   0x09

// Pins
#define GREEN_LED           2
#define RED_LED             3
#define AT_HOME_SW          4
#define GO_PREV_STEP_BT     5
#define GO_HOME_BT          6
#define GO_NEXT_STEP_BT     7

// Buttons management
#define DEBOUNCE_DELAY_MS   500L

// Commands
#define NONE                0
#define NEXT_STEP           1
#define PREVIOUS_STEP       2
#define HOMING              3

// Globals
AccelStepper stepper(AccelStepper::HALF4WIRE, 8, 9, 10, 11);
uint8_t _operation =        NONE;
unsigned long
  _lastButtonTime =         0;

// Volatiles
volatile Register _v_register;

LinkedList<long> _indexes = LinkedList<long>();

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  defaultRegister();
  initLed();
  showBusy();
  initI2c();
  initButtons();
  printDefinition();
  printRegister();
  showReady();
}

void loop(void) {
  listenButtons();
  if (_operation != NONE) {
    showBusy();
    switch(_operation) {
      case NEXT_STEP:
        Serial.println(F("Next Step"));
        goToNextStep();
        break;
      case PREVIOUS_STEP:
        Serial.println(F("Previous Step"));
        goToPreviousStep();
        break;
      case HOMING:
        Serial.println(F("Home"));
        goHome();
        break;
    }
    showReady();
    _operation = NONE;
  }
}

void defaultRegister(void) {
  _v_register.kerfMm = 2.5;
  _v_register.fingerMm = 13.0;
  _v_register.toleranceUm = 150.0;
  _v_register.offsetMm = 0.0;
}

