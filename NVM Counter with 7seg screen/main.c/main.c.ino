const uint8_t LED_PIN = 2;
const uint8_t DO_PIN = 4; // D0 (GPIO16)
const uint8_t D1_PIN = 5;  // D1 (GPIO5)
const uint16_t debounce_ms = 3000;  // Enough for a standard button press
volatile uint32_t like_update_time = 0;
volatile uint32_t dislike_update_time = 0;
volatile bool like_detected = false;
volatile bool dislike_detected = false;


void setup() {
  //Set up serial
  Serial.begin(115200);
  Serial.println("Start");
  
  // Set up LED as heartbeat
  pinMode(LED_PIN, OUTPUT);

  // Set up buttons
  pinMode(DO_PIN, INPUT_PULLUP);
  pinMode(D1_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DO_PIN), ISR_like_press, RISING);
  attachInterrupt(digitalPinToInterrupt(D1_PIN), ISR_dislike_press, RISING);

  // Set up screen

  // Set up flash memory
}; //required by ino

void loop() {
    // Detect button press -> Use ISR
    
    // Update count in LittleFS
      // Read
      // Add/Decrease
      // Write

    // Update screen with value

    // Sleep

    // Heartbeat
  #if (1)  
    digitalWrite(LED_PIN, LOW);
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
  #endif

  if(true == dislike_detected)
  {
    Serial.println("Dislike");
    dislike_detected = false;
  }

  if(true == like_detected)
  {
    Serial.println("Like");
    like_detected = false;
  }

}; //required by ino

ICACHE_RAM_ATTR void ISR_like_press() //ISR need to be on RAM in ESP8266
{ 
  if(like_update_time > millis() ) //millis() rollback
  { 
    like_update_time = 0;
  }

  if( (millis() - like_update_time) > debounce_ms)
  {
    digitalWrite(LED_PIN, LOW);
    like_detected = true;
    like_update_time = millis();
  }
};

ICACHE_RAM_ATTR void ISR_dislike_press() //ISR need to be on RAM in ESP8266
{ 
  if(dislike_update_time > millis() ) //millis() rollback
  {
    dislike_update_time = 0;
  }

  if( (millis() - dislike_update_time) > debounce_ms)
  {
    digitalWrite(LED_PIN, HIGH);
    dislike_detected = true;
    dislike_update_time = millis();
  }
};