#include <LittleFS.h>

void setup() {
  // Init Serial Communication
  Serial.begin(115200);
  Serial.println("Start");

  setupLed();
  setupButtons();
  setupISR();
  setupNvm(); // Init LittleFS
  setupLikeCounter();
  // Init screen

}

void loop() {
  
  handleHeartbeat();
  handleButtonPresses();
  handleCounterRollback();
  handleCounterUpdate();
}



