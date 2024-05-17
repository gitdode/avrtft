#!/bin/bash

set -eu
set -o pipefail

WIDTH=320
HEIGHT=240
BLOCKSIZE=512
DEVICE=/dev/mmcblk0
IMAGE="sdcard.img"

cat /dev/null > $IMAGE

for i in *.jpg; do
    bmp="${i%.*}.bmp"
    convert $i -scale ${WIDTH}x${HEIGHT} -define bmp:subtype=RGB565 "$bmp"
    size=$(stat --printf="%s" "$bmp")
    blocks=$((($size+$BLOCKSIZE-1)/$BLOCKSIZE))
    bsize=$((blocks*$BLOCKSIZE))
    truncate -s $bsize "$bmp"
    cat "$bmp" >> "$IMAGE"
    echo "$bmp" $bsize
done

sudo dd if="$IMAGE" of=$DEVICE bs=$BLOCKSIZE status=progress
