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

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2); // Set button 1 to input
	GPIO->PIN_CNF[14] = (3 << 2); // Set button 2 to input
    GPIO->PIN_CNF[15] = (3 << 2); // Set button 2 to input
    GPIO->PIN_CNF[16] = (3 << 2); // Set button 2 to input

	GPIO->PIN_CNF[17] = (1 << 0); // Set LED 1 to output
	GPIO->PIN_CNF[18] = (1 << 0); // Set LED 2 to output
	GPIO->PIN_CNF[19] = (1 << 0); // Set LED 3 to output
	GPIO->PIN_CNF[20] = (1 << 0); // Set LED 4 to output
}

int main() {
    button_init(); // Initialize buttons

    // Initialize UART
    uart_init();

    // Turn off all LEDs initially
    GPIO->OUTSET = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);

    while(1) {
        // Check for button presses and send corresponding letters
        if(!(GPIO->IN & (1 << 13))) { // Button 1 pressed

            // Turn on LED matrix: clear LED outputs (active low -> LED on)
			for (int i = 17; i <= 20; i++) {
				GPIO->OUTCLR = (1 << i);
			}
	
            uart_send('A');


        }



        if(!(GPIO->IN & (1 << 14))) { // Button 2 pressed
              // Turn on LED matrix: clear LED outputs (active low -> LED on)
			for (int i = 17; i <= 20; i++) {
				GPIO->OUTSET = (1 << i);
			}

            uart_send('B');
        }

        if (!(GPIO->IN & 1 << 15)) iprintf("The average grade in TTK%d was in %d was: %c\n\r",4235 ,2022,'B');

        // Check for received characters and toggle LEDs
        char received = uart_read();
        if(received != '\0') {
           GPIO->OUT ^= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        }
    }
} 