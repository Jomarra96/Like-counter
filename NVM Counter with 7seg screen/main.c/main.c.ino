#include <LittleFS.h>

const uint8_t D2_PIN = 4;        // D2 (GPIO4)
const uint8_t D1_PIN = 5;        // D1 (GPIO5)
const uint16_t debounce_ms = 2000;  // ESP8266/32 have issues with falling/rising edges! (https://github.com/espressif/arduino-esp32/issues/1111) 
const uint8_t LED_PIN = 2;       // LED pin

// Variables for debounce and detection states
volatile uint32_t like_update_time = 0;
volatile uint32_t dislike_update_time = 0;
volatile bool like_detected = false;
volatile bool dislike_detected = false;

int16_t like_counter = 0;
int16_t previous_like_counter = 0;

void setup() {
  // Init Serial Communication
  Serial.begin(115200);
  Serial.println("Start");

  setupLed();
  setupButtons();
  setupISR();
  setupNvm(); // Init flash memory

  if(-1 == readFile("/like_counter.txt", &like_counter)) // Try to read file, updating like_counter
  {
    // Fail: Create file, write "0000"
    writeFile("/like_counter.txt", "0000");
  }

  // Init counter update check
  previous_like_counter = like_counter;

  // Init screen
}

void loop() {
  
  handleHeartbeat();
  handleButtonPresses();
  handleCounterRollback();
  handleCounterUpdate();

  Serial.printf("Current like counter %d\n", like_counter);
}



