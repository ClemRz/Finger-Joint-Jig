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

void handleGetRoot(void) {
  sendWebPage();
}

void handlePostRoot(void) {
  _register.kerfMm = _server.arg("kerfMm").toFloat();
  _register.fingerMm = _server.arg("fingerMm").toFloat();
  _register.toleranceUm = _server.arg("toleranceUm").toFloat();
  _register.offsetMm = _server.arg("offsetMm").toFloat();
  writeConfig();
  writeArduino();
}

void sendWebPage(void) {
  String out = "";
  out.concat(F("<!DOCTYPE html><html><head><meta name=viewport content=\"initial-scale=1,maximum-scale=1,user-scalable=no\"><style>html,body{font-family:Arial;font-size:14px;background:#fff;padding:3px;color:#000;margin:0;width:100%;line-height:2em;box-sizing:border-box}section{width:350px;margin:0 auto}fieldset>legend{font-weight:bolder}header,footer{text-align:center}footer{color:#888;font-size:.75rem}.help{font-size:.8rem;font-style:italic;line-height:1em;margin:10px auto}</style></head><body><header><h1>Finger-joint jig</h1></header><section><form method=post><fieldset><legend>Settings</legend><label for=f>Finger:</label><input type=number name=fingerMm id=f min=0 max=285 step=\"0.01\" value=\""));
  out.concat(_register.fingerMm);
  out.concat(F("\"> mm<br><label for=o>Offset:</label><input type=number name=offsetMm id=o min=0 max=285 step=\"0.01\" value=\""));
  out.concat(_register.offsetMm);
  out.concat(F("\"> mm<br><label for=k>Kerf:</label><input type=number name=kerfMm id=k min=0 max=285 step=\"0.01\" value=\""));
  out.concat(_register.kerfMm);
  out.concat(F("\"> mm<br><label for=t>Tolerance:</label><input type=number name=toleranceUm id=t min=0 max=999 step=1 value=\""));
  out.concat(_register.toleranceUm);
  out.concat(F("\"> µm<br><input type=submit value=Submit></fieldset></form></section><section class=help> Hardware characteristics: <ul><li>Range: 285mm / 14757 steps</li><li>1 mm = 51.779 steps</li><li>1 step = 19µm</li></ul></section><footer> &copy; 2018 Clément Ronzon </footer></body></html>"));
  _server.send(200, F("text/html"), out);
}

