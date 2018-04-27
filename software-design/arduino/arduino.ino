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

#include <AccelStepper.h>

#define RANGE_IN_MM     285   //mm
#define RANGE_IN_STEPS  6850  //steps
#define STEPS_PER_MM    24    //setps/mm = 42µm/step
#define FULL_SPEED      1200
#define LOW_SPEED       100
#define FULL_ACC        2000
#define LOW_ACC         100

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup() {
  moveQuiclyTo(
}

void loop() {
}

void goHome(void) {
  moveQuiclyTo(0);
}

void moveQuiclyTo(int mm) {
  stepper.setMaxSpeed(FULL_SPEED);
  stepper.setAcceleration(FULL_ACC);
  moveTo(mm);
}

void moveSlowlyTo(int mm) {
  stepper.setMaxSpeed(LOW_SPEED);
  stepper.setAcceleration(LOW_ACC);
  moveTo(mm);
}

void moveTo(int mm) {
  int steps = mm * STEPS_PER_MM;
  if (steps <= RANGE_IN_STEPS) {
    stepper.moveTo(steps);
    stepper.runToPosition();
  }
}

