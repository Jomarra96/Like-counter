int16_t like_counter = 0;
int16_t previous_like_counter = 0;

void handleCounterRollback() {  //7 segment display has 4 numbers
    if(like_counter > 9999)
  {
    like_counter = 0;
  }
}

void increaseLikeCounter() {
  like_counter++;
}

void decreaseLikeCounter() {
  like_counter--;
}

void setupLikeCounter() {
  if(-1 == readFile("/like_counter.txt", &like_counter)) // Try to read file, updating like_counter
  {
    // Fail: Create file, write "0000"
    writeFile("/like_counter.txt", "0000");
  }

  // Init counter update check
  previous_like_counter = like_counter;
}

// Updates the like counter and saves it to non-volatile memory (NVM)
void handleCounterUpdate() {
  char number_char[5] = {0};
  if(previous_like_counter != like_counter) // Update NVM if counter has been updated
  {
    uint16_t like_counter_temp = like_counter;

    // Convert the counter value to a 4-digit character string
    for(uint8_t i = 0; i < 4; i++)
    {
      number_char[3-i] = (like_counter_temp%10 + 48);
      like_counter_temp /= 10;
    }
    
     // Print the current counter value and write it to the file
    Serial.printf("Current like counter %d%d%d%d\n", number_char[0]-48, number_char[1]-48, number_char[2]-48, number_char[3]-48);
    writeFile("/like_counter.txt", ( String(number_char).c_str() ) );
    
    previous_like_counter = like_counter;
  }
}

void setupNvm() {
    Serial.println("Mount LittleFS");
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
    return;
  }
  else{
    Serial.println("Little FS Mounted Successfully");
  }
}

// Reads a file from the filesystem and interprets it as a 4 digit number
int8_t readFile(const char *path, int16_t *read_num) {
  uint8_t digit_position = 3;
  uint16_t read_num_temp = 0;

  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return -1;
  }

  while (file.available()) {  // This assummes the number is saved in the format "XXXX", using leading 0s
    read_num_temp += ( (file.read() - 48)*pow(10, digit_position)); // n-48 transforms ASCII nums into dec nums. Then choose the position in the number with n*10^pos (*1000, *100, *10, *1)
    digit_position--;
  }

  *read_num = read_num_temp;
  Serial.printf("File content: %d\r\n", *read_num);

  file.close();
  return 0;
}

// Writes a string message to a file in the filesystem
void writeFile(const char *path, const char *message) {

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
  } else {
    Serial.println("Write failed");
  }
  delay(1000);  // Make sure the CREATE and LASTWRITE times are different
  file.close();
}