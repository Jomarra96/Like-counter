const uint8_t D2_PIN = 4;        // D2 (GPIO4)
const uint8_t D1_PIN = 5;        // D1 (GPIO5)
const uint16_t debounce_ms = 1000;  // ESP8266/32 have issues with falling/rising edges! (https://github.com/espressif/arduino-esp32/issues/1111) 

// Variables for debounce and detection states
volatile uint32_t like_update_time = 0;
volatile uint32_t dislike_update_time = 0;
volatile bool like_detected = false;
volatile bool dislike_detected = false;

const uint8_t LED_PIN = 2;       // LED pin

void setupButtons(){
    // Set up buttons as inputs with pull-up resistors
    pinMode(D1_PIN, INPUT_PULLUP);
    pinMode(D2_PIN, INPUT_PULLUP);    
}

void setupISR(){
  // Attach interrupts for button presses
  attachInterrupt(digitalPinToInterrupt(D1_PIN), ISR_like_press, RISING);
  attachInterrupt(digitalPinToInterrupt(D2_PIN), ISR_dislike_press, RISING);
}

void handleButtonPresses() {
  if (like_detected) {
    updateLikeStatus();
    increaseLikeCounter();
  }

  if (dislike_detected) {
    updateDislikeStatus();
    decreaseLikeCounter();
  }
}

static void updateLikeStatus() {
  Serial.println("Like");
  like_detected = false;
  // Update NVM
}

static void updateDislikeStatus() {
  Serial.println("Dislike");
  dislike_detected = false;
  // Update NVM
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