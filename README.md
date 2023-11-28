# AVRTFT

Simple project to drive a TFT LCD like the 
[Adafruit 1.8" Color TFT LCD 160x128 ST7735R](https://www.adafruit.com/product/358)
with an AVR MCU (ATmega328P) and avr-libc.  

Currently implemented:

* Mostly complete UTF-8 set (code points U+0000 to U+00FF) of Hack font
  with antialiasing (4-Bit greyscale)
* Some emojis (16-Bit RGB)
* Write text in Hack including emojis 🙂
* Draw bitmaps
* Write text and bitmaps via USART
* Upload BMP images via USART (16-Bit (5/6/5) RGB)
* Logging via USART

The AVR is clocked with a crystal for reliable communication via USART.

Ideas:

* Read pictures from SD Card
* Display 4K@50Hz videos...

![IMG_20231125_011054](https://github.com/gitdode/avrtft/assets/11530253/cd3d94eb-fb16-4d78-9eaa-bebfec8f8ef7)

## Write something via USART

Connect to the controller with for example GTKTerm (38400 Baud).  
Write some text and a bitmap, and upload a BMP image:

`c 0xffff` // clear display  
`d` // display the demo  
`t 0 0 Just some text` // write text in Hack to row 0 column 0  
`b 0 0 1` // write bitmap with index 0 (tiny Linus cat) to row 0 column 0  
`p 0 0` // prepare to "stream" a 16-Bit (5/6/5) RGB BMP image  

## Enter emojis

Emojis are entered with a tabulation char + their "code", i.e. `Smile!<TAB>s`.
