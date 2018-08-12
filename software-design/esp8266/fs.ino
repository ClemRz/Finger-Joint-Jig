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
 
void initFS(void) {
  SPIFFS.begin();
  readConfig();
}

void writeConfig(void) {
  Serial.print(F("Saving configuration..."));
  File file = SPIFFS.open(CONFIG_FILE_PATH, "w");
  if (file) {
    DynamicJsonBuffer jsonBuffer(JSON_OBJECT_SIZE(156));
    JsonObject& root = jsonBuffer.createObject();
    root["k"] = _register.kerfMm;
    root["f"] = _register.fingerMm;
    root["t"] = _register.toleranceUm;
    root["o"] = _register.offsetMm;
    root.printTo(file);
    file.close();
    Serial.println(F("done."));
  } else {
    Serial.print(F("Failed to write ")); Serial.println(CONFIG_FILE_PATH);
  }
}

void readConfig(void) {
  Serial.print(F("Reading configuration..."));
  File file = SPIFFS.open(CONFIG_FILE_PATH, "r");
  if (file) {
    if(file.available()) {
      DynamicJsonBuffer jsonBuffer(JSON_OBJECT_SIZE(156));
      JsonObject& root = jsonBuffer.parseObject(file.readString());
      _register.kerfMm = root["k"];
      _register.fingerMm = root["f"];
      _register.toleranceUm = root["t"];
      _register.offsetMm = root["o"];
      Serial.print(F("..."));
    }
    file.close();
    Serial.println(F("done."));
  } else {
    Serial.print(F("Failed to read ")); Serial.println(CONFIG_FILE_PATH);
    defaultRegister();
  }
}

