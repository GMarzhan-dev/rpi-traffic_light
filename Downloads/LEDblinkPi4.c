#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/* The base address of the GPIO peripheral (ARM Physical Address) */
#define GPIO_BASE       0xfe200000 //BCM2711 GPIO Base Address
#define GPIO_LENGTH     (4*1024)

#define GPIO_GPFSEL0    0
#define GPIO_GPFSEL1    1
#define GPIO_GPFSEL2    2
#define GPIO_GPFSEL3    3
#define GPIO_GPFSEL4    4
#define GPIO_GPFSEL5    5

#define GPIO_GPSET0     7
#define GPIO_GPSET1     8

#define GPIO_GPCLR0     10
#define GPIO_GPCLR1     11

#define LED_GPFSEL      GPIO_GPFSEL4
#define LED_GPFBIT      21
#define LED_GPSET       GPIO_GPSET1
#define LED_GPCLR       GPIO_GPCLR1
#define LED_GPIO_BIT    15

/* Pointer to the mapped GPIO registers */
volatile uint32_t *gpio;

int main(int argc, char *argv[])
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        printf("can't open /dev/mem\n");
        return 1;
    }

    gpio = mmap(NULL, GPIO_LENGTH, PROT_READ | PROT_WRITE,
                MAP_SHARED, fd, GPIO_BASE);
    if (gpio == (void *) -1) {
        printf("can't mmap\n");
        return 1;
    }

    /* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
       peripheral register to enable GPIO16 as an output */
    gpio[2] |= 1 << 6 ;

    /* This loop runs forever */
    while (1) {
        /* Set the LED GPIO pin low */
        gpio[10] = 1 << 22;

        sleep(1);

        /* Set the LED GPIO pin high */
        gpio[7] = 1 << 22;

        sleep(1);
    }
}
