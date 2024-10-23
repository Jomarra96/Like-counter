#include <Arduino.h>
#include <LittleFS.h>
#include <TM1637Display.h>

void setup() {
  // Init Serial Communication
  Serial.begin(115200);
  Serial.println("Start");

  setupLed();
  setupButtons();
  setupISR();
  setupNvm(); // Init LittleFS
  setupLikeCounter();
  setup_display();
}

void loop() {
  static int16_t like_count = 0;
  static int16_t temp_like_count = 0;

  getCounter(&like_count);
  temp_like_count = like_count;

  handleButtonPresses();
  handleCounterRollback();
  handleCounterUpdate();

  getCounter(&like_count);
  if(temp_like_count != like_count)
  {
    update_display();
  }
}



