#!/bin/bash

# set up the terminal for communication with the controller
stty -F /dev/ttyUSB0 speed 38400 cs8 -parenb -cstopb raw

# clear the display all black and write all the emojis...
echo "c ffff" > /dev/ttyUSB0
sleep 1
echo -e "t 0 0 Hello Emojis!" > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 0 \ts' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 16 \tb' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 32 \tg' > /dev/ttyUSB0
sleep 0.1
# echo -e 't 16 48 \tn' > /dev/ttyUSB0
# sleep 0.1
echo -e 't 16 48 \tm' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 64 \th' > /dev/ttyUSB0
sleep 0.1
echo -e 't 16 80 \tt' > /dev/ttyUSB0
sleep 0.1
# echo -e 't 16 112 \te' > /dev/ttyUSB0
# sleep 0.1
echo -e 't 16 96 \ta' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 0 \tU' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 16 \tD' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 32 \tS' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 48 \tA' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 64 \tu' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 80 \to' > /dev/ttyUSB0
sleep 0.1
echo -e 't 32 96 \tO' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 0 \tH' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 16 \tB' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 32 \tP' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 48 \tT' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 64 \tF' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 80 \tR' > /dev/ttyUSB0
sleep 0.1
echo -e 't 48 96 \tC' > /dev/ttyUSB0
