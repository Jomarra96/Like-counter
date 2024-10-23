// Module connection pins (Digital Pins)
#define CLK 14  // D5 (GPIO14)
#define DIO 12  // D6 (GPIO12)
#define BITDELAY 10

TM1637Display display(CLK, DIO, BITDELAY);
static int16_t like_count = 0;

  // Init screen
void setup_display() {
  display.setBrightness(0x04, true);
  getCounter(&like_count);
  update_display();
}

void update_display(){
  display.clear();
  getCounter(&like_count);
  display.showNumberDec(like_count, true);
}