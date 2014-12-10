uio-hotplug-test
================

Sample kernel and userspace driver for testing uio-hotplug feature.

## uio_fake_hotplug.c
A `uio` kernel driver that fakes _hot-unplug_. Registers itself as a `platform_device`. On inserting the module, it starts a `kthread` which will call `uio_unregister_device()` after a delay of ~*3 secs*. This should test if the kernel can handle hot-unplug while the user-space program is still accessing the device. Interrupts are faked using a timer.

## uio_user.c
A `uio` user-space driver. This simply opens the uio device and `mmap`s a page size of the uio device memory and continously writes to it. It has two modes of operation:
* Repeatedly write to the `mmap` space (by doing `memset` on it).
* Wait for interrupt, before writing to the `mmap` space. This can be enabled by defining `WAIT_FOR_INTERRUPT`.

## run-uio-stress.sh
A simple script that loads the uio kernel driver, calls the uio user driver, removes the uio kernel driver and sleeps for 1 sec.

## Run
Run the test:
```
$ make clean
$ make
$ ./run-uio-stress.sh
```
Monitor the kernel logs for error/bug trace:
```
$ tail -100f /var/log/kern.log
```

