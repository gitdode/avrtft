#!/bin/bash

# set up the terminal for communication with the controller
stty -F /dev/ttyUSB0 speed 38400 cs8 -parenb -cstopb raw

# clear the display all black and write all the emojis...
echo "c ffff\t" > /dev/ttyUSB0
sleep 0.1
echo -e "t 0 0 Hello Emojis!" > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 0 \ts' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 16 \tb' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 32 \tg' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 48 \tn' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 64 \tm' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 80 \th' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 96 \tt' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 112 \te' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 0 \ta' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 16 \tU' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 32 \tD' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 48 \tS' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 64 \tA' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 80 \tu' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 96 \to' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 112 \tH' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 0 \tB' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 16 \tP' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 32 \tT' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 48 \tF' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 64 \tR' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 80 \tC' > /dev/ttyUSB0
