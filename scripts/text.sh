#!/bin/bash

# set up the terminal for communication with the controller
stty -F /dev/ttyUSB0 speed 38400 cs8 -parenb -cstopb raw

# clear the display all black
# echo "c ffff" > /dev/ttyUSB0
sleep 1.5
# inefficiently write some more text line by line on a 800x480 display
echo "t 0 0 Bärtierchen (Tardigrada) - auch Wasserbären genannt - bilden einen Tierstamm innerhalb der " > /dev/ttyUSB0
sleep 1.5
echo "t 0 16 Häutungstiere (Ecdysozoa). Die meistens weniger als einen Millimeter großen achtbeinigen Tiere " > /dev/ttyUSB0
sleep 1.5
echo "t 0 32 erinnern durch ihr Aussehen und ihre tapsig wirkende Fortbewegungsweise etwas an Bären, was zu ihrer " > /dev/ttyUSB0
sleep 1.5
echo "t 0 48 Bezeichnung im deutschen Sprachraum führte. Auch ihr wissenschaftlicher Name (von lateinisch " > /dev/ttyUSB0
sleep 1.5
echo "t 0 64 tardigradus 'langsam schreitend, langsam', zusammengesetzt aus tarde 'langsam' und gradi 'Schritte " > /dev/ttyUSB0
sleep 1.5
echo "t 0 80 machen, schreiten, einherschreiten')[1] geht auf die langsame Fortbewegung zurück. " > /dev/ttyUSB0
sleep 1.5
echo "t 0 96 " > /dev/ttyUSB0
sleep 1.5
echo "t 0 112 Sie leben weltweit im Meer, Süßwasser oder in feuchten Lebensräumen an Land; besonders häufig " > /dev/ttyUSB0
sleep 1.5
echo "t 0 128 findet man sie dort in Mooskissen. Eine Eigenschaft der Tiere ist die Kryptobiose, ein " > /dev/ttyUSB0
sleep 1.5
echo "t 0 144 todesähnlicher Zustand, in dem sie extreme Umweltbedingungen überdauern können. Bärtierchen können " > /dev/ttyUSB0
sleep 1.5
echo "t 0 160 sich sowohl vom Inhalt von Pflanzenzellen ernähren als auch räuberisch von kleinen Tieren wie " > /dev/ttyUSB0
sleep 1.5
echo "t 0 176 Fadenwürmern (Nematoda) oder Rädertierchen (Rotifera), die sie dazu anstechen und aussaugen. " > /dev/ttyUSB0
sleep 1.5
echo "t 0 192 Bärtierchen pflanzen sich meistens geschlechtlich fort. Manche Arten vermehren sich aber auch " > /dev/ttyUSB0
sleep 1.5
echo "t 0 208 parthenogenetisch, das heißt ohne Beteiligung von Männchen; die Eier der Weibchen entwickeln sich " > /dev/ttyUSB0
sleep 1.5
echo "t 0 224 in diesem Fall ohne Befruchtung." > /dev/ttyUSB0
sleep 1.5
echo "t 0 240 " > /dev/ttyUSB0
sleep 1.5
echo "t 0 256 Die nächsten heute noch lebenden Verwandten der Bärtierchen sind vermutlich Glieder- (Arthropoda) " > /dev/ttyUSB0
sleep 1.5
echo "t 0 272 und Stummelfüßer (Onychophora), mit denen sie das Taxon Panarthropoda bilden. " > /dev/ttyUSB0
sleep 1.5