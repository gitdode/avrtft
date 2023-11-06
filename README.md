# AVRTFT

Project to drive a TFT LCD like the 
[Adafruit 1.8" Color TFT LCD 160x128 ST7735R](https://www.adafruit.com/product/358)
with an AVR MCU (ATmega328P) and avr-libc.  

Currently implemented:

* Nearly complete UTF-8 set (code points U+0000 to U+00FF) of GNU Unifont
* Small subset of large glyphs in DejaVu: 0-9 and some special characters
* Store font and bitmaps in program memory instead of RAM
* Draw strings in Unifont and DejaVu
* Draw bitmaps
* Write text and bitmaps via USART
* Logging via USART

Thanks to:  

* [https://github.com/adafruit/Adafruit-ST7735-Library](https://github.com/adafruit/Adafruit-ST7735-Library) 
for helping me out with the display initialization!  

## Write something via USART

Connect to the controller with for example GTKTerm (9600 Baud).  
Write some text and a bitmap:

TODO...