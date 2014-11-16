#!/bin/sh

START_FILE="S95zig"
USB_FILE="flashbot-port.conf"
ANDROID_DIR="/.android"
EXE_FILE="usbwidget"

if [ ! -d "./data" ]; then
    echo "not found install dir:data!"
    exit 1;
fi

if [ ! -f "/etc/$USB_FILE" ]; then
    echo "not found usb configure file:/etc/flashbot-port.conf"
    exit 2;
fi


if [ ! -f "/etc/init.d/$START_FILE" ]; then
    dos2unix ./data/$START_FILE
    cp ./data/$START_FILE /etc/init.d
    chmod 755 /etc/init.d/$START_FILE
fi

if [ ! -d "$ANDROID_DIR" ]; then
    mkdir $ANDROID_DIR
    chmod 755 $ANDROID_DIR
fi

cp data/$EXE_FILE /usr/local/bin
chmod 755 /usr/local/bin/$EXE_FILE

exit 0
