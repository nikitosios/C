# Makefile – makefile of my first driver
 
ifneq (${KERNELRELEASE},)
    obj-m := ofd.o
else
    KERNEL_SOURCE := /usr/src/linux
    PWD := $(shell pwd)
default:
    ${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules
 
clean:
    ${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
endif

