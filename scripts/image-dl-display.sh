#!/bin/sh

# set the storage directory
DIR="/tmp"

# check for argument with image download url
if [ "$1" == "" ]; then
  echo "ERROR: expecting URL of image to display"
  return 0
fi

# check image type 
FILE=""
jpg=$(echo $1 | grep -i jpg)
png=$(echo $1 | grep -i png)
if [ "$jpg" != "" ]; then
  FILE=".jpg"
elif [ "$png" != "" ]; then
  FILE=".png"
else 
  echo "Expecting JPG or PNG image"
fi


NOW=$(date +"%Y-%m-%d_%H-%M-%S")
FILENAME=$(echo "img_${NOW}${FILE}")

# download the image file
wget -O $FILENAME $1 

# display to the screen
killall fbi
fbi -d /dev/fb0 -notty -nocomments --noverbose $FILENAME
