#!/bin/bash

while true; do

	sudo insmod uio_fake_hotplug.ko
	sudo ./uio_user
	sudo rmmod uio_fake_hotplug

	sleep 1
done;

