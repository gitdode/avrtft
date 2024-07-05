# AVRTFT

Experimental project to drive a TFT LCD with an AVR MCU (ATmega328P) and avr-libc.  

Currently supported displays/drivers:

* [Adafruit 1.8" Color TFT LCD 160x128 ST7735R](https://www.adafruit.com/product/358)
* [Adafruit 2.0" Color IPS TFT 320x240 ST7789](https://www.adafruit.com/product/4311)
* [Adafruit 2.8" Color TFT LCD with Cap Touch 320x240 ILI9341](https://www.adafruit.com/product/2090)

Additionally, there is some support for larger (up to 800x480) TTL displays, for example the
[Adadruit 7.0" 40-pin TFT Display - 800x480 with Touchscreen](https://www.adafruit.com/product/2354),
with the RA8875 controller like the
[RA8875 Driver Board for 40-pin TFT Touch Displays - 800x480 Max](https://www.adafruit.com/product/1590) 
including touch support.

Currently implemented features:

* Mostly complete UTF-8 set (code points U+0000 to U+00FF) of Hack font
  with antialiasing (4-Bit greyscale)
* Some emojis (16-Bit RGB)
* Write text in Hack including emojis 🙂
* Draw bitmaps
* Write text and bitmaps via USART
* Upload BMP images via USART (16-Bit 5/6/5 RGB)
* Basic SD card support: read and write blocks of 512 bytes
* Read BMP images from SD card (raw)
* Process touch events (FT6206, RA8875)
* Very basic paint application
* Logging via USART

Ideas:

* Make features usable from a touch screen menu

![IMG_20231125_011054](https://github.com/gitdode/avrtft/assets/11530253/cd3d94eb-fb16-4d78-9eaa-bebfec8f8ef7)

## Write something via USART

Connect to the controller with for example GTKTerm (38400 Baud).  
Write some text and a bitmap, and upload a BMP image:

`c 0xffff` // clear display  
`d` // display the demo  
`t 0 0 Just some text` // write text in Hack to row 0 column 0  
`b 0 0 1` // write bitmap with index 1 (tiny Linus cat) to row 0 column 0  
`p 0 0` // prepare to "stream" a 16-Bit (5/6/5) RGB BMP image to row 0 column 0    
`cat Bali160x128.bmp > /dev/ttyUSB0` // upload a BMP image  
`s 0` // read BMP image from SD card starting at address 0 (to row 0 column 0)  
`a` // start paint application

## Enter emojis

Emojis are entered with a tabulation char + their "code", i.e. `Smile!<TAB>s` for a smiling emoji.

![IMG_20231129_004922](https://github.com/gitdode/avrtft/assets/11530253/3a6cbcdd-d004-48d9-a227-ba21f91dac0b)

## Convert and write images to SD card

Without any file system, to write any number of pictures with a specific 
resolution as 16-Bit (5/6/5) RGB BMP image files:

1. Convert pictures with ImageMagick 'convert' and pad them to a multiple of 
512 bytes

        for i in *.jpg; do convert $i -scale 320x240 -define bmp:subtype=RGB565 $i.bmp; truncate -s 154112 $i.bmp; echo $i; done

2. Concatenate the images to a single file

        for i in *.bmp; do cat $i >> sdcard.img; echo $i; done

3. Write the images raw to SD card (danger zone!)

        sudo dd if=sdcard.img of=/dev/mmcblk0 bs=512

Now the images can be read one by one from SD card with an address offset of `301`.

## Paint application

A super basic paint application created to learn about processing touch events 
and draw something on the screen.  

The FT6206 based touch screen of the 
[Adafruit 2.8" Color TFT LCD with Cap Touch 320x240 ILI9341](https://www.adafruit.com/product/2090)
works quite well but at least for me the coordinates of touches close to the 
long edges of the screen are a bit off (too close to the edge) and there seems 
to be no calibration capability - the data sheet mentions "auto calibration".

But still it is fun and it should be possible to create an application 
supporting touch with reliable usability. 

![IMG_20240103_134738](https://github.com/gitdode/avrtft/assets/11530253/5e9947cc-e236-49e7-a06b-1dbfffa304b7)

## Larger (up to 800x480) TTL displays

If at all possible, it probably is quite a challenge to drive such a 40-pin display with a 28-pin 
MCU like the ATmega238P, but it is easy with the RA8875 driver, offering support for a touch screen 
as well. Here it is combined with the [SparkFun Level Shifting microSD Breakout](https://www.sparkfun.com/products/13743) 
to read images from an SD card, advancing to the next image by touching the screen.

![IMG_20240704_214710](https://github.com/gitdode/avrtft/assets/11530253/a09af16d-0dcf-4c1f-a8d6-0fb965b75fda)

