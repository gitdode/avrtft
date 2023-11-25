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
* Stream BMP images via USART
* Logging via USART

Ideas:

* Read pictures from SD Card
* Display 4K@50Hz videos...

The AVR is clocked with a crystal for reliable communication via USART.

![IMG_20231118_225206](https://github.com/gitdode/avrtft/assets/11530253/747ad970-1306-48a2-8a7a-978977b5b7d4)

## Write something via USART

Connect to the controller with for example GTKTerm (9600 Baud).  
Write some text and a bitmap, and upload a BMP image:

`c 0xffff` // clear display  
`d` // display the demo  
`t 0 0 h Just some text` // write text in Hack to row 0 column 0  
`b 0 112 0` // write bitmap with index 0 ('blush' emoji) to row 0 column 224  
`p 0 0` // prepare to "stream" a 16-Bit (5/6/5) RGB BMP image  
