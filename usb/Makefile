all :
	/home/lijing/tools/buildroot/output/external-toolchain/bin/arm-none-linux-gnueabi-gcc -c usb_enum.c -g -Wall
	/home/lijing/tools/buildroot/output/external-toolchain/bin/arm-none-linux-gnueabi-gcc -c adb_utils.c -g -Wall
	ar rcs libusb_enum.a usb_enum.o adb_utils.o
sample:
	/home/lijing/tools/buildroot/output/external-toolchain/bin/arm-none-linux-gnueabi-gcc sample.c -L. -lusb_enum -o sample -g -Wall -lpthread -static
sa:
	/home/lijing/tools/buildroot/output/external-toolchain/bin/arm-none-linux-gnueabi-gcc -c usb_enum.c -g -Wall
	/home/lijing/tools/buildroot/output/external-toolchain/bin/arm-none-linux-gnueabi-gcc -c adb_utils.c -g -Wall
	ar rcs libusb_enum.a usb_enum.o adb_utils.o
	/home/lijing/tools/buildroot/output/external-toolchain/bin/arm-none-linux-gnueabi-gcc sample.c -L. -lusb_enum -o sample -g -Wall -lpthread -static
	/home/lijing/tools/buildroot/output/external-toolchain/bin/arm-none-linux-gnueabi-gcc -o usb usb.c -g -Wall
pc-all:
	gcc -c usb_enum.c -g -Wall
	gcc -c adb_utils.c -g -Wall
	ar rcs libusb_enum.a usb_enum.o adb_utils.o
pc-sample:
	gcc sample.c -L. -lusb_enum -o sample -g -Wall -lpthread -static
pd:
	gcc -c usb_enum.c -g -Wall
	gcc -c adb_utils.c -g -Wall
	ar rcs libusb_enum.a usb_enum.o adb_utils.o
	gcc sample.c -L. -lusb_enum -o sample -g -Wall -lpthread -static
clean:
	rm -rf *.o *.a sample
