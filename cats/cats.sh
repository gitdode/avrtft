#!/bin/sh

# set up the terminal for communication with the controller
stty -F /dev/ttyUSB0 speed 38400 cs8 -parenb -cstopb raw

# clear the display all black and write some text in Hack font, and so on...
echo "c 0" > /dev/ttyUSB0
sleep 1
echo "t 12 20  Katzen... " > /dev/ttyUSB0
sleep 1
echo "t 44 56  Katzen... " > /dev/ttyUSB0
sleep 1
echo "t 80 92  Katzen! " > /dev/ttyUSB0

sleep 1

# prepare sending a BMP image file, then send the image, and so on...
echo "p 0 0" > /dev/ttyUSB0
cat Chico160x128.bmp > /dev/ttyUSB0
sleep 3
echo "p 0 0" > /dev/ttyUSB0
cat Tamy160x128.bmp > /dev/ttyUSB0
sleep 3
echo "p 0 0" > /dev/ttyUSB0
cat Linus160x128.bmp > /dev/ttyUSB0
sleep 3
echo "p 0 0" > /dev/ttyUSB0
cat Bali160x128.bmp > /dev/ttyUSB0
