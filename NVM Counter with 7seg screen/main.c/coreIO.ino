const uint8_t D1_PIN = 5;        // D1 (GPIO5)
const uint8_t D2_PIN = 4;        // D2 (GPIO4)
const uint8_t D7_PIN = 13;        // D7 (GPIO13)
const uint16_t debounce_ms = 1000;  // ESP8266/32 have issues with falling/rising edges! (https://github.com/espressif/arduino-esp32/issues/1111) 

// Variables for debounce and detection states
volatile uint32_t like_update_time = 0;
volatile uint32_t dislike_update_time = 0;
volatile uint32_t rst_update_time = 0;
volatile bool like_detected = false;
volatile bool dislike_detected = false;
volatile bool reset_counter_detected = false;

const uint8_t LED_PIN = 2;       // LED pin

void setupButtons(){
    // Set up buttons as inputs with pull-up resistors
    pinMode(D1_PIN, INPUT_PULLUP);
    pinMode(D2_PIN, INPUT_PULLUP);
    pinMode(D7_PIN, INPUT_PULLUP);    
}

void setupISR(){
  // Attach interrupts for button presses. Edge type doesn't matter. ESP32 treats both as the same.
  attachInterrupt(digitalPinToInterrupt(D1_PIN), ISR_like_press, FALLING);
  attachInterrupt(digitalPinToInterrupt(D2_PIN), ISR_dislike_press, FALLING);
  attachInterrupt(digitalPinToInterrupt(D7_PIN), ISR_reset_counter, FALLING);
}

void handleButtonPresses() {
  if (like_detected) {
    Serial.println("Like");
    like_detected = false;
    increaseLikeCounter();
  }

  if (dislike_detected) {
    Serial.println("Dislike");
    dislike_detected = false;
    decreaseLikeCounter();
  }

  if (reset_counter_detected) {
    Serial.println("Counter reset");
    reset_counter_detected = false;
    resetCounter();
  }
}

// ISRs
IRAM_ATTR static void ISR_like_press() {
  // Debouncing for like button press
  if (like_update_time > millis()) {
    like_update_time = 0;
  }

  if ((millis() - like_update_time) > debounce_ms) {  //Check for debounce time
    like_detected = true; 
    like_update_time = millis();
  }
}

IRAM_ATTR static void ISR_dislike_press() {
  // Debouncing for dislike button press
  if (dislike_update_time > millis()) {
    dislike_update_time = 0;
  }

  if ((millis() - dislike_update_time) > debounce_ms) { //Check for debounce time
    dislike_detected = true;
    dislike_update_time = millis();
  }
}

IRAM_ATTR static void ISR_reset_counter() {
  // Debouncing for dislike button press
  if (rst_update_time > millis()) {
    rst_update_time = 0;
  }

  if ((millis() - rst_update_time) > debounce_ms) { //Check for debounce time
    reset_counter_detected = true;
    rst_update_time = millis();
  }
}

void setupLed() {
    // Set up LED pin as output
    pinMode(LED_PIN, OUTPUT);
}

void handleHeartbeat() {
#if (1)  
  digitalWrite(LED_PIN, LOW);
  delay(500);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
#endif
}
