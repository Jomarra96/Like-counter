#if (0)
void handleButtonPresses();
static void updateLikeStatus();
static void updateDislikeStatus();
void setup_buttons();
void setup_ISR();
void handleButtonPresses(); // Handle detected button presses from ISR

// Interrupt Service Routines (ISR)
IRAM_ATTR static void ISR_like_press();
IRAM_ATTR static void ISR_dislike_press();
#endif

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
    like_counter++;
  }

  if (dislike_detected) {
    updateDislikeStatus();
    like_counter--;
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
    digitalWrite(LED_PIN, LOW);
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
    digitalWrite(LED_PIN, HIGH);
    dislike_detected = true;
    dislike_update_time = millis();
  }
}