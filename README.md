Raspberry Pi Low-Level GPIO Control
This repository contains C implementations for controlling Raspberry Pi GPIO pins using direct memory mapping. These projects demonstrate low-level hardware-software interfacing without relying on high-level libraries like WiringPi or pigpio.

# Projects Overview
1. Traffic Light Controller (traffic.c)
A simulation of a traffic light sequence using direct register manipulation via /dev/gpiomem.

Key Features:

Uses mmap to map GPIO registers into the process memory space.

Implements a state machine for Red, Yellow, and Green light transitions.

Includes a "blinking" phase for transitions using usleep.

Technical Detail: Direct bitwise operations on GPSET and GPCLR registers to toggle specific pins.

2. Standalone LED Blinker (t_led.c)
A robust implementation for blinking the onboard ACT (Activity) LED or external LEDs on a Raspberry Pi.

Key Features:

Accesses /dev/mem for physical memory addressing (requires root privileges).

Targets BCM_GPIO pin 47 (Standard for RPi 2/3 ACT LED).

Includes error handling for memory mapping and root access verification.

Uses nanosleep for high-precision timing intervals.

# Hardware Requirements
Platform: Raspberry Pi (Tested on RPi 2 / RPi 4).

Peripherals: LEDs, resistors (for the traffic light setup), and jumper wires.

# Getting Started
Prerequisites
Ensure you have gcc installed on your Raspberry Pi:

Bash

sudo apt-get update
sudo apt-get install build-essential
*Compilation
You can compile the files using the following commands:

Bash

# Compile Traffic Light Controller
gcc -o traffic_light traffic_light.c

# Compile LED Blinker
gcc -o led_blink led_blink.c
Running the Programs
Since these programs access physical memory locations, they require administrative privileges:

Bash

# Run Traffic Light
sudo ./traffic_light

# Run LED Blinker
sudo ./led_blink
# Safety Note
Direct memory access (/dev/mem) is powerful but can be risky if incorrect addresses are written to. Always double-check your register offsets and bitmasks according to the BCM2835/BCM2711 ARM Peripherals datasheet.

👨‍💻 Author
GMarzhan-dev

Computer Engineering Student

Focus: Embedded Systems & Hardware-Software Interfacing
