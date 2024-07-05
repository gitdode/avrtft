#!/bin/bash

# set up the terminal for communication with the controller
stty -F /dev/ttyUSB0 speed 38400 cs8 -parenb -cstopb raw

# clear the display all black and write all the emojis...
echo "c ffff" > /dev/ttyUSB0
sleep 1
echo -e "t 0 0 Hello Emojis!" > /dev/ttyUSB0
sleep 0.2
echo -e 't 0 16 \ts' > /dev/ttyUSB0
sleep 0.2
echo -e 't 16 16 \tb' > /dev/ttyUSB0
sleep 0.2
echo -e 't 32 16 \tg' > /dev/ttyUSB0
# sleep 0.2
# echo -e 't 48 16 \tn' > /dev/ttyUSB0
sleep 0.2
echo -e 't 48 16 \tm' > /dev/ttyUSB0
sleep 0.2
echo -e 't 64 16 \th' > /dev/ttyUSB0
sleep 0.2
echo -e 't 80 16 \tt' > /dev/ttyUSB0
# sleep 0.2
# echo -e 't 112 16 \te' > /dev/ttyUSB0
sleep 0.2
echo -e 't 96 16 \ta' > /dev/ttyUSB0
sleep 0.2
echo -e 't 0 32 \tU' > /dev/ttyUSB0
sleep 0.2
echo -e 't 16 32 \tD' > /dev/ttyUSB0
sleep 0.2
echo -e 't 32 32 \tS' > /dev/ttyUSB0
sleep 0.2
echo -e 't 48 32 \tA' > /dev/ttyUSB0
sleep 0.2
echo -e 't 64 32 \tu' > /dev/ttyUSB0
sleep 0.2
echo -e 't 80 32 \to' > /dev/ttyUSB0
# sleep 0.2
# echo -e 't 96 32 \tO' > /dev/ttyUSB0
sleep 0.2
echo -e 't 0 48 \tH' > /dev/ttyUSB0
sleep 0.2
echo -e 't 16 48 \tB' > /dev/ttyUSB0
sleep 0.2
echo -e 't 32 48 \tP' > /dev/ttyUSB0
sleep 0.2
echo -e 't 48 48 \tT' > /dev/ttyUSB0
sleep 0.2
echo -e 't 64 48 \tF' > /dev/ttyUSB0
sleep 0.2
echo -e 't 80 48 \tR' > /dev/ttyUSB0
# sleep 0.2
# echo -e 't 96 48 \tC' > /dev/ttyUSB0
