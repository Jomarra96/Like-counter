# BOARD

[Lolin NodeMCU ESP8266](https://www.make-it.ca/nodemcu-details-specifications/)
4MB Flash, 64KB RAM

HW I had on hand
Widely supported, allows C, C++, Arduino and uPy

# FW

Chose Arduino over bare C, uPy, etc.

**Advantages**

Does the trick and enables for quickest implementation, without hitting its limits.
- Available drivers for TM16xx
- Simple code
- LittleFS supported
- Flash time/size irrelevant for this project
- Got ISR needed for button detection
	
**Disadvantages**
- No debugging in most boards
- Flashing takes >30s
- Huge initial size, lots of boilerplate (>200KB)
- Lots of externs, hard to follow fns

# SCREEN

[7 Segment display](https://www.amazon.de/dp/B07XQ2M188?ref=ppx_yo2ov_dt_b_fed_asin_title)

- simple and cheap. low power can be achieved by only lighting the display momentarily after button press. TM16XX Driver included

# BUTTON

[Standard push button](https://www.amazon.de/gp/product/B0BXZZTH26/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)

Like - D1 (GPIO4)

Dislike - D2 (GPIO5)

# CASE

3D printed

# POWER

Wall adapter available -> 5V + regulator to 3v3

# Non Volatile Memory

Flash in ESP8266