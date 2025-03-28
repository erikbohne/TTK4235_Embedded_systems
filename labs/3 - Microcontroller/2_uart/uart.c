#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t RESERVED0[3];
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED3[7];
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED5[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED6[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED7[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED8[1];
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED9[17];
    volatile uint32_t BAUDRATE;
} NRF_UART_REG;

void uart_init() {
    // Configure GPIO pins for UART
    GPIO->PIN_CNF[6] = 1; // TXD pin
    GPIO->PIN_CNF[8] = 0; // RXD pin

    // Configure UART
    UART->PSELTXD = 6;  // TXD pin
    UART->PSELRXD = 8;  // RXD pin
    UART->PSELCTS = 0xFFFFFFFF; // Disable CTS
    UART->PSELRTS = 0xFFFFFFFF; // Disable RTS
    UART->BAUDRATE = 0x00275000; // 9600 baud
    UART->ENABLE = 4; // Enable UART
    UART->TASKS_STARTRX = 1; // Start receiving
}

void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while(!UART->EVENTS_TXDRDY);
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;
}

char uart_read() {
    if(UART->EVENTS_RXDRDY) {
        UART->EVENTS_RXDRDY = 0;
        return UART->RXD;
    }
    return '\0';
} 