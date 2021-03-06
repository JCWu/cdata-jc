obj-m := cdata.o

#KDIR := /home/android/android-kernel/common
#KDIR := /usr/src/linux-headers-2.6.32-28-generic/
KDIR :=/usr/src/linux-headers-2.6.35-22-generic/
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c
