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

void initI2c(void) {
  Wire.begin(SLAVE_I2C_ADDRESS);
  Wire.onReceive(isrOnI2cReceive);
}

void isrOnI2cReceive(int numBytes) {
  showBusy();
  uint8_t i = 0;
  while (Wire.available()) {
    if (i < REG_MAP_SIZE) { // Read enough bytes to fill the register
      _v_register.byteAt[i] = Wire.read();
      i++;
    } else Wire.read(); // Ignore the rest of it
  }
  Serial.print("_v_register.kerfMm: "); Serial.println(_v_register.kerfMm);
  Serial.print("_v_register.fingerMm: "); Serial.println(_v_register.fingerMm);
  Serial.print("_v_register.toleranceUm: "); Serial.println(_v_register.toleranceUm);
  Serial.print("_v_register.offsetMm: "); Serial.println(_v_register.offsetMm);
  showFree();
}
