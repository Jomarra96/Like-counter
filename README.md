# ESP8266 Like Box

A like counter box with buttons, a screen and permanent memory.

This device detects Like/Dislike/Rst button presses and displays the current counter on a 7-segment screen. The counter value is protected against power failures by routinely storing it on the device Flash.

## Background

I currently work in automotive, so it was obvious I had to print the infamous [AUTOSAREEEE](https://www.reddit.com/r/embedded/comments/leq366/comment/gmiq6d0/) post and stick it on a wall by the office. Given most of my colleagues pretty much breathe AUTOSAR .arxml's, I now want to measure how fond they are of the omnipresent standard.

Could I have just gotten a commercial option? Absolutely. Do they look ugly AF? Yep. Plus, I also wanted to hack something with a little personality.

## Behavior

On Like/Dislike/Flash buttons press, the internal counter updates, then gets stored in Flash and displayed on screen.
On power up, it tries reading a valid value from flash. Otherwise the counter resets.

## Replicate

Get the files in your machine, download LittleFS and TM1637Display libraries from the IDE and flash into the ESP8266 board. Follow the pinout from \Docs\Wiring. Other ESP8266 versions may not work.

## Features

R1 Display like count.

R2 Detect like.

R3 Detect dislike.

R4 Detect reset.

R5 Keep counter on power off.

R6 Mountable on a foam wall.

R7 Cost <20EUR.

R8 Dev time <1mo - <20h total time.

## TODO

Nothing, all done