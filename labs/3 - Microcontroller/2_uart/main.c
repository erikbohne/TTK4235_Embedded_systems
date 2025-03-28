#include <stdio.h>
#include <sys/types.h>
#include "uart.h"
#include "gpio.h"

ssize_t _write(int fd, const void *buf, size_t count) {
    char *letter = (char *)(buf);
    for(int i = 0; i < count; i++) {
        uart_send(*letter);
        letter++;
    }
    return count;
}

int main() {
    // Configure LED matrix
    GPIO->PIN_CNF[4] = 1; // LED 1
    GPIO->PIN_CNF[5] = 1; // LED 2
    GPIO->PIN_CNF[6] = 1; // LED 3
    GPIO->PIN_CNF[7] = 1; // LED 4

    // Configure buttons
    GPIO->PIN_CNF[13] = 0; // Button 1
    GPIO->PIN_CNF[14] = 0; // Button 2

    // Initialize UART
    uart_init();

    // Turn off all LEDs initially
    GPIO->OUTCLR = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);

    while(1) {
        // Check for button presses and send corresponding letters
        if(!(GPIO->IN & (1 << 13))) { // Button 1 pressed
            uart_send('A');
        }
        if(!(GPIO->IN & (1 << 14))) { // Button 2 pressed
            uart_send('B');
        }

        // Check for received characters and toggle LEDs
        char received = uart_read();
        if(received != '\0') {
            GPIO->OUT ^= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        }
    }
} 