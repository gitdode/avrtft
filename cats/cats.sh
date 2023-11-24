#!/bin/sh

echo "c 0" > /dev/ttyUSB0
sleep 1
echo "t 20 12 h  Katzen... " > /dev/ttyUSB0
sleep 1
echo "t 56 44 h  Katzen... " > /dev/ttyUSB0
sleep 1
echo "t 92 80 h  Katzen! " > /dev/ttyUSB0

sleep 1
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
