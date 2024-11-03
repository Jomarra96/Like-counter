# Review | Retro

FW took around 8h from start of design to completion. I Doubt that would have been possible with standalone C, missing the TM1637 and LittleFS libraries I had with Arduino. Arduino IDE v2 still behaves weirdly with c/h files, since most library functions have hiddend dependencies for which you need the whole .ino #include set. To modularize your code, you must create new .ino files at the same level! Annoying for everything but the smallest programs. Anyways, Arduino turned out to be a good choice for this specific project.

- Code documentation could have been easily implemented in Doxygen. FW diagram should have been done at the beginning, instead of at the end (Lazy me).

- Mechanical design took 2 iterations and a clogged hotend. For the future, ensure the modelled support pieces actually match the real ones!

- Cost was under 16EUR due to availability of parts, total time spent was around 18h, with most of it on FW and Mech design.

All requirements are met, so I consider the project a success.

# Improvements

Portability could easily be achieved with a 18650, by keeping the 7-seg display on for just a couple seconds and enabling low power on the SoC - [0.3mA without linear regulator](https://tinker.yeoman.digital/2016/05/29/running-nodemcu-on-a-battery-esp8266-low-power-consumption-revisited/). A paper display could also be used to lengthen battery life, although with a steep increase in price. (Have fun with the drivers and implementation if you want [Real low power](https://www.amazon.de/s?k=paper+display+%2B+driver&__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=3PCOA0LQ88L14&sprefix=paper+display+%2B+drive%2Caps%2C96&ref=nb_sb_noss))