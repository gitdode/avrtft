# AVRTFT

Simple project to drive a TFT LCD with an AVR MCU (ATmega328P) and avr-libc.  

Currently supported displays/drivers:

* [Adafruit 1.8" Color TFT LCD 160x128 ST7735R](https://www.adafruit.com/product/358)
* [Adafruit 2.0" Color IPS TFT 320x240 ST7789](https://www.adafruit.com/product/4311)
* [Adafruit 2.8" Color TFT LCD with Cap Touch 320x240 ILI9341](https://www.adafruit.com/product/2090)

Currently implemented features:

* Mostly complete UTF-8 set (code points U+0000 to U+00FF) of Hack font
  with antialiasing (4-Bit greyscale)
* Some emojis (16-Bit RGB)
* Write text in Hack including emojis 🙂
* Draw bitmaps
* Write text and bitmaps via USART
* Upload BMP images via USART (16-Bit 5/6/5 RGB)
* Logging via USART
* Basic capacitive touch support (FT6206)

The AVR is clocked with a crystal for reliable communication via USART.

Ideas:

* Support touch
* Read pictures from SD Card
* Display 4K@50Hz videos...

![IMG_20231125_011054](https://github.com/gitdode/avrtft/assets/11530253/cd3d94eb-fb16-4d78-9eaa-bebfec8f8ef7)

## Write something via USART

Connect to the controller with for example GTKTerm (38400 Baud).  
Write some text and a bitmap, and upload a BMP image:

`c 0xffff` // clear display  
`d` // display the demo  
`t 0 0 Just some text` // write text in Hack to row 0 column 0  
`b 0 0 1` // write bitmap with index 1 (tiny Linus cat) to row 0 column 0  
`p 0 0` // prepare to "stream" a 16-Bit (5/6/5) RGB BMP image to row 0 column 0    
`cat Bali160x128.bmp > /dev/ttyUSB0` // upload a "fullscreen" BMP image  

## Enter emojis

Emojis are entered with a tabulation char + their "code", i.e. `Smile!<TAB>s` for a smiling emoji.

![IMG_20231129_004922](https://github.com/gitdode/avrtft/assets/11530253/3a6cbcdd-d004-48d9-a227-ba21f91dac0b)
