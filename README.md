uio-hotplug-test
================

Sample kernel and userspace driver for testing uio-hotplug feature.

## uio_dummy.c
The UIO kernel driver. Registers itself as a `platform_device` with `uio`. On inserting the module, it starts a `kthread` which will call `uio_unregister_device()` after a delay of ~*3 secs*. This should test if the kernel can handle _hot-unplug_ while the user-space program is still accessing the device. Interrupts are faked using a timer.

## uio_user.c
The UIO user-space driver. This simply opens the uio device and `mmap`s a page size of the uio device memory. It has two modes of operation:
* Just access the `mmap` space (by doing `memset` on it).
* Wait for interrupt, before writing to the `mmap` space. This can be enabled by defining `WAIT_FOR_INTERRUPT`.

## run-uio-stress.sh
A simple script that loads the uio kernel driver, then calls uio user driver, removes the uio kernel driver and sleeps for 1 sec.

## Run
Run the test:
    $ make clean
    $ make
    $ ./run-uio-stress.sh

Monitor the kernel logs for error/bug trace:
    $ tail -100f /var/log/kern.log

