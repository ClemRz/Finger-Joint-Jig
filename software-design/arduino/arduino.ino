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

#include <Wire.h>
#include <AccelStepper.h>
#include "register.h"

// Stepper settings
#define RANGE_IN_MM       285     //mm
#define RANGE_IN_STEPS    14757   //steps
#define STEPS_PER_MM      51.779  //setps/mm
#define MM_PER_STEP       0.019   //mm/step
#define FULL_SPEED        1800    //steps/s = 34.763 mm/s
#define LOW_SPEED         150     //steps/s = 2.897 mm/s
#define FULL_ACC          4000    //steps/s2 = 77.251 mm/s2
#define LOW_ACC           200     //steps/s2 = 3.863 mm/s2

// i2c settings
#define SLAVE_I2C_ADDRESS 0x09

// Pins
#define GO_STEP_BT        2
#define GO_HOME_BT        3
#define AT_HOME_SW        8
#define RED_LED           9
#define GREEN_LED         10

// Buttons management
#define DEBOUNCE_DELAY_MS 500L

// Commands
#define NONE              0
#define STEP              1
#define HOMING            2

// Globals
AccelStepper stepper(AccelStepper::HALF4WIRE, 4, 5, 6, 7);

// Volatiles
volatile unsigned long
  _v_lastStepIsrTime =    0,
  _v_lastHomeIsrTime =    0;
volatile uint8_t _v_operation = NONE;
volatile Register _v_register;

void setup(void) {
  Serial.begin(115200);
  Serial.println();
  defaultRegister();
  initLed();
  showBusy();
  initI2c();
  initButtons();
  Serial.print("_v_register.kerfMm: "); Serial.println(_v_register.kerfMm);
  Serial.print("_v_register.fingerMm: "); Serial.println(_v_register.fingerMm);
  Serial.print("_v_register.toleranceUm: "); Serial.println(_v_register.toleranceUm);
  Serial.print("_v_register.offsetMm: "); Serial.println(_v_register.offsetMm);
  showFree();
}

void loop(void) {
  if (_v_operation != NONE) {
    Serial.println(_v_operation == STEP ? "Step" : "Home");
    showBusy();
    switch(_v_operation) {
      case STEP:
        goToNextStep();
        break;
      case HOMING:
        goHome();
        break;
    }
    showFree();
    _v_operation = NONE;
  }
}

void defaultRegister(void) {
  _v_register.kerfMm = 2.5;
  _v_register.fingerMm = 13.0;
  _v_register.toleranceUm = 150.0;
  _v_register.offsetMm = 0.0;
}

