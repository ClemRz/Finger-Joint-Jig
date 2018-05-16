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

float getPositionMm(void) {
  return (float)getPositionIndex() / STEPS_PER_MM;
}

long getPositionIndex(void) {
  return stepper.currentPosition();
}

void goHome(void) {
  setFast();
  stepper.move(-2 * RANGE_IN_STEPS);
  while (!isAtHome()) stepper.run();
  stepper.setMaxSpeed(LOW_SPEED);
  stepper.stop();
  stepper.setCurrentPosition(0);
}

void moveQuicly(float mm) {
  setFast();
  move(mm);
}

void moveSlowly(float mm) {
  Serial.print(F("Move ")); Serial.print(mm); Serial.println(F("mm"));
  setSlow();
  move(mm);
}

void moveQuiclyTo(float mm) {
  setFast();
  moveTo(mm);
}

void moveSlowlyTo(float mm) {
  setSlow();
  moveTo(mm);
}

void moveSlowlyToIndex(long index) {
  setSlow();
  moveToIndex(index);
}

void setSlow(void) {
  stepper.setMaxSpeed(LOW_SPEED);
  stepper.setAcceleration(LOW_ACC);
}

void setFast(void) {
  stepper.setMaxSpeed(FULL_SPEED);
  stepper.setAcceleration(FULL_ACC);
}

//Relative position
void move(float mm) {
  int index = stepper.currentPosition() + round(mm * STEPS_PER_MM);
  Serial.print(F("Move ")); Serial.print(round(mm * STEPS_PER_MM)); Serial.println(F(" steps"));
  moveToIndex(index);
}

//Absolute position
void moveTo(float mm) {
  long index = round(mm * STEPS_PER_MM);
  moveToIndex(index);
}

void moveToIndex(long index) {
  if (index >= 0 && index <= RANGE_IN_STEPS) {
    stepper.runToNewPosition(index);
  }
}
