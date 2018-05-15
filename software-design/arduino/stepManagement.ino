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

 void goToNextStep(void) {
  float 
    x = getPositionMm(),
    k = _v_register.kerfMm,
    offset = _v_register.offsetMm == 0.0 ? 0.0 : _v_register.offsetMm + _v_register.toleranceUm / 2000,
    finger = _v_register.fingerMm,
    space = _v_register.fingerMm + _v_register.toleranceUm / 1000,
    p = finger + space;
  Serial.print(F("x: ")); Serial.println(x);
  Serial.print(F("k: ")); Serial.println(k);
  Serial.print(F("offset: ")); Serial.println(offset);
  Serial.print(F("finger: ")); Serial.println(finger);
  Serial.print(F("space: ")); Serial.println(space);
  Serial.print(F("p: ")); Serial.println(p);
  if (MM_PER_STEP < offset - x) { //We need to cut the offset blank
    Serial.println(F("x < offset"));
    stepOneKerf(offset - x);
  } else {
    Serial.println(F("x >= offset"));
    x -= offset;
    Serial.print(F("x: ")); Serial.println(x);
    x = fmod(x, p);
    Serial.print(F("fmod(x, p): ")); Serial.println(fmod(x, p));
    Serial.print(F("x: ")); Serial.println(x);
    Serial.print(F("p - x: ")); Serial.println(p - x);
    if (isnan(x) || isinf(x)) return;
    if (p - x < MM_PER_STEP) x -= p;
    Serial.print(F("x: ")); Serial.println(x);
    Serial.print(F("finger + k - x: ")); Serial.println(finger + k - x);
    if (MM_PER_STEP < finger + k - x) { //We need to move to the next blank
      Serial.println(F("x < finger + k"));
      moveSlowly(finger + k - x);
    } else { //We need to cut the blank
      Serial.println(F("x >= finger + k"));
      stepOneKerf(p - x);
    }
  }
 }

 void stepOneKerf(float remainingMm) {
  moveSlowly(min(_v_register.kerfMm, remainingMm));
 }

