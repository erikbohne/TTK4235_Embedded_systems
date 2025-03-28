#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t TASKS_STARTRX;    // 0x000 Start UART receiver
    volatile uint32_t TASKS_STOPRX;     // 0x004 Stop UART receiver
    volatile uint32_t TASKS_STARTTX;    // 0x008 Start UART transmitter
    volatile uint32_t TASKS_STOPTX;     // 0x00C Stop UART transmitter
    volatile uint32_t RESERVED0[3];     // Padding for 0x010 - 0x018
    volatile uint32_t TASKS_SUSPEND;    // 0x01C Suspend UART
    
    volatile uint32_t RESERVED1[7];     // Padding for 0x020 - 0x0FC
    
    volatile uint32_t EVENTS_CTS;       // 0x100 CTS is activated (set low). Clear To Send.
    volatile uint32_t EVENTS_NCTS;      // 0x104 CTS is deactivated (set high). Not Clear To Send.
    volatile uint32_t EVENTS_RXDRDY;    // 0x108 Data received in RXD
    volatile uint32_t RESERVED2[1];     // Padding for 0x10C - 0x118
    volatile uint32_t EVENTS_TXDRDY;    // 0x11C Data sent from TXD
    volatile uint32_t EVENTS_ERROR;     // 0x124 Error detected
    volatile uint32_t RESERVED3[3];     // Padding for 0x128 - 0x140
    volatile uint32_t EVENTS_RXTO;      // 0x144 Receiver timeout
    
    volatile uint32_t RESERVED4[3];     // Padding for 0x148 - 0x1FC
    
    volatile uint32_t SHORTS;           // 0x200 Shortcut register
    
    volatile uint32_t RESERVED5[12];    // Padding for 0x204 - 0x2FC
    
    volatile uint32_t INTENSET;         // 0x304 Enable interrupt
    volatile uint32_t INTENCLR;         // 0x308 Disable interrupt
    
    volatile uint32_t RESERVED6[28];    // Padding for 0x30C - 0x47C
    
    volatile uint32_t ERRORSRC;         // 0x480 Error source
    
    volatile uint32_t RESERVED7[7];     // Padding for 0x484 - 0x4FC
    
    volatile uint32_t ENABLE;           // 0x500 Enable UART
    
    volatile uint32_t RESERVED8[3];     // Padding for 0x504 - 0x508
    
    volatile uint32_t PSELRTS;          // 0x508 Pin select for RTS
    volatile uint32_t PSELTXD;          // 0x50C Pin select for TXD
    volatile uint32_t PSELCTS;          // 0x510 Pin select for CTS
    volatile uint32_t PSELRXD;          // 0x514 Pin select for RXD
    
    volatile uint32_t RESERVED9[2];     // Padding for 0x518 - 0x520
    
    volatile uint32_t RXD;              // 0x518 RXD register
    volatile uint32_t TXD;              // 0x51C TXD register
    
    volatile uint32_t BAUDRATE;         // 0x524 Baud rate
    
    volatile uint32_t RESERVED10[10];   // Padding for 0x528 - 0x56C
    
    volatile uint32_t CONFIG;  
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