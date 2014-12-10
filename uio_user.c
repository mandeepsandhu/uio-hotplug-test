#include <stdio.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define WAIT_FOR_INTERRUPT

int main()
{
    int uiofd, intr_cnt = 0;
    void *map_addr;
    fd_set readset;

    uiofd = open("/dev/uio0", O_RDWR);
    if (uiofd < 0) {
        perror("uio open:");
        return errno;
    }

    long page_size = getpagesize();
    map_addr = mmap(NULL, page_size,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED, uiofd, 0);

    // Hammer away!
    while (1) {
#ifdef WAIT_FOR_INTERRUPT
        FD_ZERO(&readset);
        FD_SET(uiofd, &readset);
        if (select(uiofd + 1, &readset, NULL, NULL, NULL) <= 0) {
            perror("select:");
            break;
        }
        if (FD_ISSET(uiofd, &readset)) {
            if (read(uiofd, &intr_cnt, 4) != 4) {
                perror("uio read:");
                break;
            }
            printf("intr count %d\n", intr_cnt);
            memset(map_addr, 0, page_size);
        }
#else
        memset(map_addr, 0, page_size);
#endif
    }
    
    munmap(map_addr, page_size);
    close(uiofd);
    return 0;
}

