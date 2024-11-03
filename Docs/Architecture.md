# SYSTEM

## BOARD

[Lolin NodeMCU ESP8266](https://www.make-it.ca/nodemcu-details-specifications/)
4MB Flash, 64KB RAM. Noice.

HW I had laying around.
Widely supported, allows C, C++, Arduino and uPy

## SCREEN

[7 Segment display](https://www.amazon.de/dp/B07XQ2M188?ref=ppx_yo2ov_dt_b_fed_asin_title)

- Simple and cheap. TM16XX Driver included.

## BUTTONS

[Standard push button](https://www.amazon.de/gp/product/B0BXZZTH26/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1).

## CASE

3D printed.

## POWER

Wall adapter available nearby -> 5V into ESP8266 microUSB. No battery or Low power needed.

## Non Volatile Memory

Flash in ESP8266

# SW Framework

I Chose Arduino over bare C, uPy, etc. I know, I know, it's just for children, hobbyists and PHD's, but hear me out.
I haven't played with it in over 4 years, and they got version 2.0 now!

**Advantages**
- Allows for quickest implementation, without hitting its limits in this simple project.
- There are available drivers for TM16xx & LittleFS on ESP8266(!!)
	
**Disadvantages**
- No debugging in most boards
- Flashing takes >30s. Ew. Apparently they include by default a metric ton of std libs, if not all of them. Ewww.
- Huge footprint, lots of boilerplate because of the previously stated (>200KB).
- Abuse of externs/macros, hard to follow fns.
- Multiple bugs within the IDE

Now, will Arduino be worth it? Hope so, check the review file for an answer!