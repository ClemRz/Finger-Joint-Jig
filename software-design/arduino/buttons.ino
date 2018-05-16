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

void initButtons(void) {
  pinMode(AT_HOME_SW, INPUT_PULLUP);
  pinMode(GO_NEXT_STEP_BT, INPUT_PULLUP);
  pinMode(GO_PREV_STEP_BT, INPUT_PULLUP);
  pinMode(GO_HOME_BT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GO_NEXT_STEP_BT), isrNextStepButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(GO_PREV_STEP_BT), isrPreviousStepButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(GO_HOME_BT), isrHomeButton, FALLING);
}

bool isAtHome(void) {
  return !digitalRead(AT_HOME_SW);
}

void isrNextStepButton(void) {
  if (millis() - _v_lastNextStepIsrTime > (unsigned long)DEBOUNCE_DELAY_MS) _v_operation = NEXT_STEP;
  _v_lastNextStepIsrTime = millis();
}

void isrPreviousStepButton(void) {
  if (millis() - _v_lastPreviousStepIsrTime > (unsigned long)DEBOUNCE_DELAY_MS) _v_operation = PREVIOUS_STEP;
  _v_lastPreviousStepIsrTime = millis();
}

void isrHomeButton(void) {
  if (millis() - _v_lastHomeIsrTime > (unsigned long)DEBOUNCE_DELAY_MS) _v_operation = HOMING;
  _v_lastHomeIsrTime = millis();
}
