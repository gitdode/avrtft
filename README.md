# AVRTFT

Simple project to drive a TFT LCD like the 
[Adafruit 1.8" Color TFT LCD 160x128 ST7735R](https://www.adafruit.com/product/358)
with an AVR MCU (ATmega328P) and avr-libc.  

Currently implemented:

* Mostly complete UTF-8 set (code points U+0000 to U+00FF) of Hack font
  with antialiasing (4-Bit greyscale)
* Small subset of large glyphs in DejaVu: 0-9 and some special characters
* Draw strings in Hack and DejaVu
* Draw bitmaps (emojis)
* Write text and bitmaps via USART
* Logging via USART

Ideas:

* Write pictures via USART (probably too slow)
* Read pictures from SD Card
* Display 4K@50Hz videos...

![IMG_20231118_223050](https://github.com/gitdode/avrtft/assets/11530253/338461b8-8cb2-428a-b46d-f24a6478fba8)

## Write something via USART

Connect to the controller with for example GTKTerm (9600 Baud).  
Write some text and a bitmap:

`c 0xffff` // clear display  
`t 0 0 h Just some text` // write text in Hack to row 0 column 0  
`b 0 112` // write bitmap with index 0 ('blush' emoji) to row 0 column 224  
`d` // display the demo  
