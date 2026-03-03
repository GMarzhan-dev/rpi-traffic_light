#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define GPIO_BASE 0xFE200000 // Virtual memory address for GPIO
#define GPIO_LEN  4*1024       // Total size of GPIO registers block

volatile uint32_t *gpio;
// Function to print binary values grouped by 4 bits

void print_binary(uint32_t value) {
    for (int i = 31; i >= 0; i--) {
        printf("%c", '0' + ((value >> i) & 1));
        if (i % 4 == 0) printf(" "); // Group digits into sets of 4
    }
    printf("\n");
}

int main() {
    int mem_fd;
    void *gpio_map;
    volatile uint32_t *gpio;

    // Open /dev/mem for memory mapping
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        perror("Cannot open /dev/mem (try running as root)");
        return -1;
    }

    // Map GPIO memory to user space
    gpio = mmap(
        NULL,                   // Map to any available address
        GPIO_LEN,               // Map the size of GPIO registers
        PROT_READ | PROT_WRITE, // Read/write access
        MAP_SHARED,             // Shared memory mapping
        mem_fd,                 // File descriptor for /dev/mem
        GPIO_BASE               // Offset to GPIO base address
    );

    if (gpio == MAP_FAILED) {
        perror("mmap failed");
        close(mem_fd);
        return -1;
    }

    

    // Print all GPIO Function Select registers (GPFSEL0 through GPFSEL5)
    for (int i = 0; i < 6; i++) {
        printf("GPFSEL%d: ", i);
        print_binary(gpio[i]); // GPFSELx offsets: 0x00, 0x04, ..., 0x14
    }

    // Print both GPIO Set registers (GPSET0 and GPSET1)
    printf("GPSET0:  ");
    print_binary(gpio[7]); // GPSET0 offset: 0x1C
    printf("GPSET1:  ");
    print_binary(gpio[8]); // GPSET1 offset: 0x20

    // Print both GPIO Clear registers (GPCLR0 and GPCLR1)
    printf("GPCLR0:  ");
    print_binary(gpio[10]); // GPCLR0 offset: 0x28
    printf("GPCLR1:  ");
    print_binary(gpio[11]); // GPCLR1 offset: 0x2C

    // Print both GPIO Level registers (GPLEV0 and GPLEV1)
    printf("GPLEV0:  ");
    print_binary(gpio[13]); // GPLEV0 offset: 0x34
    printf("GPLEV1:  ");
    print_binary(gpio[14]); // GPLEV1 offset: 0x38

    // Unmap the memory and close the file descriptor
    munmap((void *)gpio, GPIO_LEN);
    close(mem_fd);

    return 0;
}
