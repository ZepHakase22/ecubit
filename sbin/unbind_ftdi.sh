#!/bin/sh

# traverse sysfs to find the USB ID
# of the USB device which is parent/ancestor of ttyUSB*
# something like "1-1.6:1.0"
TTYDEV=$(basename $DEVNAME)
BOUND_DEVICES=/sys/bus/usb/drivers/ftdi_sio/*/
for DEVICE in ${BOUND_DEVICES}; do
	if [ -e $DEVICE/$TTYDEV ]; then
		USBID=$(basename $DEVICE)
		break
	fi
done

echo "$USBID" > /sys/bus/usb/drivers/ftdi_sio/unbind
echo "$USBID" >/home/zep/unbind_ftdi
