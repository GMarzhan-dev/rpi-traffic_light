#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
    if (fd < 0) return -1;

    volatile unsigned int *gpio = (unsigned int *)mmap(
        NULL,
        4096,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );

    if (gpio == MAP_FAILED) return -1;

    *(gpio + 1) = 0b00000000000000000000001000001001;

    while(1) {

        *(gpio + 7) = 0b00000000000000000000010000000000;
        sleep(2);

        *(gpio + 7) = 0b00000000000000000000110000000000;
        sleep(2);

        *(gpio + 10) = 0b00000000000000000000110000000000;
        *(gpio + 7)  = 0b00000000000000000010000000000000;
        sleep(3);

        *(gpio + 10) = 0b00000000000000000010000000000000;

        for(int i=0; i<3; i++) {
            *(gpio + 7)  = 0b00000000000000000000100000000000;
            usleep(500000);
            *(gpio + 10) = 0b00000000000000000000100000000000;
            usleep(500000);
        }
    }

    return 0;
}
