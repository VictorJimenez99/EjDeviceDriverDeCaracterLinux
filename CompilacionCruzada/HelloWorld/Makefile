obj-m += hello_world.o

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/victor/linux M=$(PWD) modules
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/victor/linux M=$(PWD) clean
