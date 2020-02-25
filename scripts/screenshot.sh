#!/bin/sh

## create a screenshot from what's currently on the display

ffmpeg \
  -vcodec rawvideo \
  -f rawvideo \
  -pix_fmt rgb565 \
  -s 320x240 \
  -i /dev/fb0 \
  \
  -f image2 \
  -vcodec mjpeg \
  screen-shot-`date +'%s'`.jpg

