#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

void configure_gpio(){
    GPIO->PIN_CNF[13] = (3 << 2); // Set button 1 to input

    GPIO->PIN_CNF[17] = (1 << 0); // Set LED 1 to output
    GPIO->PIN_CNF[18] = (1 << 0); // Set LED 2 to output
    GPIO->PIN_CNF[19] = (1 << 0); // Set LED 3 to output
    GPIO->PIN_CNF[20] = (1 << 0); // Set LED 4 to output
    
}


void configure_gpiote(void) {
    // Configure GPIOTE channel 0 for output
    GPIOTE->CONFIG[0] = (1 << 16) | (13 << 8) | (1 << 0); // OUT, pin 13, LoToHigh, event

    GPIOTE->CONFIG[1] = (1 << 20)|(3 << 16) | (17 << 8) | (3 << 0); // OUT, pin 17, Toggle, task
    GPIOTE->CONFIG[2] = (1 << 20)|(3 << 16) | (18 << 8) | (3 << 0); // OUT, pin 18, LoToHigh, task
    GPIOTE->CONFIG[3] = (1 << 20)|(3 << 16) | (19 << 8) | (3 << 0); // OUT, pin 19, Toggle, task
    GPIOTE->CONFIG[4] = (1 << 20)|(3 << 16) | (20 << 8) | (3 << 0); // OUT, pin 20, LoToHigh, task
}

void configure_ppi(void) {
    // Enable the PPI channel
    PPI->CHENSET = (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);

    // Configure PPI channel 0 to trigger GPIOTE task on GPIOTE event
    PPI->PPI_CH[0].EEP = (uint32_t)&GPIOTE->EVENTS_IN[0];
    PPI->PPI_CH[0].TEP = (uint32_t)&GPIOTE->TASKS_OUT[1];

    PPI->PPI_CH[1].EEP = (uint32_t)&GPIOTE->EVENTS_IN[0];
    PPI->PPI_CH[1].TEP = (uint32_t)&GPIOTE->TASKS_OUT[2];

    PPI->PPI_CH[2].EEP = (uint32_t)&GPIOTE->EVENTS_IN[0];
    PPI->PPI_CH[2].TEP = (uint32_t)&GPIOTE->TASKS_OUT[3];

    PPI->PPI_CH[3].EEP = (uint32_t)&GPIOTE->EVENTS_IN[0];
    PPI->PPI_CH[3].TEP = (uint32_t)&GPIOTE->TASKS_OUT[4];
}


int main() {
    // Configure GPIO
    configure_gpio();

    // Configure GPIOTE
    configure_gpiote();

    // Configure PPI
    configure_ppi();

    // Enable GPIOTE events
    //GPIOTE->INTENSET = (1 << 0);

    while (1) {
        // Main loop does nothing, all work is done in interrupts
    }

    return 0;
}

