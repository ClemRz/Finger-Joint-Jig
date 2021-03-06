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
 
#ifndef _REGISTER_H
#define _REGISTER_H

#define REG_MAP_SIZE  16  // Size of the register (consider nuber of bytes)

/**
 * ===================== /!\ =====================
 * 
 * we need to use float and not double in order to keep
 * compatibility between Arduino and ESP8266:
 * 
 *  bytes   float     double
 * Arduino    4         4
 * ESP8266    4         8
 * 
 * https://github.com/esp8266/Arduino/blob/master/tools/sdk/include/c_types.h
 * 
 * ===============================================
 */

typedef struct {
  union {
    byte byteAt[REG_MAP_SIZE];
    struct {                            // bytes:
      float kerfMm;                     // 4
      float fingerMm;                   // 4
      float toleranceUm;                // 4
      float offsetMm;                   // 4
    };
  };
} Register;

#endif  //_REGISTER_H
