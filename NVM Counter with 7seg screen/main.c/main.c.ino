// Constants and Pin Definitions
const uint8_t LED_PIN = 2;       // LED pin
const uint8_t D2_PIN = 4;        // D2 (GPIO4)
const uint8_t D1_PIN = 5;        // D1 (GPIO5)
const uint16_t debounce_ms = 2000;  // ESP8266/32 have [issues](https://github.com/espressif/arduino-esp32/issues/1111) with falling/rising edges!

// Variables for debounce and detection states
volatile uint32_t like_update_time = 0;
volatile uint32_t dislike_update_time = 0;
volatile bool like_detected = false;
volatile bool dislike_detected = false;

// Function Declarations
void setup();
void loop();
static void handleButtonPresses();
static void handleHeartbeat();
static void updateLikeStatus();
static void updateDislikeStatus();

// Interrupt Service Routines (ISR)
IRAM_ATTR static void ISR_like_press();
IRAM_ATTR static void ISR_dislike_press();

//----------------------------
// Setup Function
//----------------------------

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  Serial.println("Start");

  // Set up LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Set up buttons as inputs with pull-up resistors
  pinMode(D1_PIN, INPUT_PULLUP);
  pinMode(D2_PIN, INPUT_PULLUP);

  // Attach interrupts for button presses
  attachInterrupt(digitalPinToInterrupt(D1_PIN), ISR_like_press, RISING);
  attachInterrupt(digitalPinToInterrupt(D2_PIN), ISR_dislike_press, RISING);

  // Set up screen (Placeholder, add actual screen setup code here)

  // Set up flash memory (Placeholder, add actual flash setup code here)
}

void loop() {
  // Handle heartbeat (LED blink)
  handleHeartbeat();

  // Handle detected button presses from ISR
  handleButtonPresses();

  // Sleep or idle if needed (Placeholder, you can add power management here)
}

//----------------------------
// Helper Functions
//----------------------------

static void handleButtonPresses() {
  if (like_detected) {
    updateLikeStatus();  // Handle like detected
  }

  if (dislike_detected) {
    updateDislikeStatus();  // Handle dislike detected
  }
}

static void handleHeartbeat() {
#if (0)  
  // Heartbeat: Blink LED every 500 ms
  digitalWrite(LED_PIN, LOW);
  delay(500);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
#endif
}

static void updateLikeStatus() {
  Serial.println("Like");
  like_detected = false;
  // Add more logic here to update flash memory or screen, if necessary
}

static void updateDislikeStatus() {
  Serial.println("Dislike");
  dislike_detected = false;
  // Add more logic here to update flash memory or screen, if necessary
}

//----------------------------
// Interrupt Service Routines (ISR)
//----------------------------

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
