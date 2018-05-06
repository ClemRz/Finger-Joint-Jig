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
#define RANGE_IN_STEPS    6850    //steps
#define STEPS_PER_MM      24.035  //setps/mm = 42µm/step
#define FULL_SPEED        1200    //1200
#define LOW_SPEED         100
#define FULL_ACC          2000    //2000
#define LOW_ACC           100

// i2c settings
#define SLAVE_I2C_ADDRESS 0x09

// Pins
#define AT_HOME_SW        6
#define GO_STEP_BT        7
#define GO_HOME_BT        8
#define RED_LED           9
#define GREEN_LED         10

// Buttons management
#define DEBOUNCE_DELAY_MS 10L

// Commands
#define NONE              0
#define STEP              1
#define HOMING            2

// Globals
AccelStepper stepper;

// Volatiles
volatile unsigned long
  _v_lastStepIsrTime =    0,
  _v_lastHomeIsrTime =    0;
volatile uint8_t _v_operation = NONE;
volatile Register
  _v_register = {2.5, 13.0, 150.0, 0};

void setup(void) {
  initLed();
  showBusy();
  initI2c();
  initButtons();
  //moveQuiclyTo(142.5);
  //moveSlowly(-20);
  //moveQuiclyTo(RANGE_IN_MM);
  //goHome();
  showFree();
}

void loop(void) {
  if (_v_operation != NONE) {
    showBusy();
    switch(_v_operation) {
      case STEP:
        goStep();
        break;
      case HOMING:
        goHome();
        break;
    }
    showFree();
    _v_operation = NONE;
  }
}

