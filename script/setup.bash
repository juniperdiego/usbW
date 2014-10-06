#!/bin/sh

POINTER_FILE="pointercal"
START_FILE="S95zig"
USB_FILE="flashbot-port.conf"
ANDROID_DIR="/.android"
EXE_FILE="usbwidget"

if [ ! -d "./data" ]; then
    echo "not found install dir:data!"
    exit 1;
fi

if [ ! -f "/etc/$POINTER_FILE" ]; then
    cp ./data/$POINTER_FILE /etc
fi


if [ ! -f "/etc/$USB_FILE" ]; then
#    cp ./data/$USB_FILE /etc
    echo "not found usb configure file:/etc/flashbot-port.conf"
    exit 2;
fi


if [ ! -f "/etc/init.d/$START_FILE" ]; then
    dos2unix ./data/$START_FILE
    cp ./data/$START_FILE /etc/init.d
fi

if [ ! -d "$ANDROID_DIR" ]; then
    mkdir $ANDROID_DIR
    chmod 755 $ANDROID_DIR
fi

cp data/$EXE_FILE /mnt/repos
chmod 755 /mnt/repos/$EXE_FILE

exit 0
