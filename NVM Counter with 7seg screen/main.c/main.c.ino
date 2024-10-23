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

// Constants and Pin Definitions

static int8_t file_status = -1;

// "Main" ino
void setup();
void loop();

#if (0)
// Button/LED
void handleHeartbeat();

//FS
void initialize_lfs();
void writeFile();
int8_t readFile();
#endif

//----------------------------
// Setup Function
//----------------------------

void setup() {
  // Init Serial Communication
  Serial.begin(115200);
  Serial.println("Start");

  // Init IO
  setup_led();
  setup_buttons();
  setup_ISR();

  // Init flash memory
  static int16_t like_counter = 0;
  initialize_lfs();
  writeFile("/like_counter.txt", "12");
  readFile("/like_counter.txt", &like_counter);
  Serial.printf("Current like counter %d", like_counter);

  // Init screen
}

void loop() {
  handleHeartbeat();
  handleButtonPresses();
}

// LFS

static void initialize_lfs() {
    Serial.println("Mount LittleFS");
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
    return;
  }
  else{
    Serial.println("Little FS Mounted Successfully");
  }
}


static int8_t readFile(const char *path, int16_t *read_num) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return -1;
  }

  while (file.available()) { 
    *read_num = file.read();
    Serial.printf("int read from file: %d\r\n", *read_num);
  }
  file.close();
  return 0;
}

static void writeFile(const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  delay(2000);  // Make sure the CREATE and LASTWRITE times are different
  file.close();
}
