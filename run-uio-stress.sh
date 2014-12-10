#!/bin/bash

while true; do

	sudo insmod uio_dummy.ko
	sudo ./uio_user
	sudo rmmod uio_dummy

	sleep 1
done;

