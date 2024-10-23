void setup_led() {
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
