#ifndef GPIOTE_H
#define GPIOTE_H
#include <stdint.h>

#define GPIOTE ((NRF_GPIOTE_REG*)0x40006000)

typedef struct {
	volatile uint32_t TASKS_OUT[8];
	volatile uint32_t RESERVED0[4];
	volatile uint32_t TASKS_SET[8];
	volatile uint32_t RESERVED1[4];
	volatile uint32_t TASKS_CLR[8];
	volatile uint32_t RESERVED3[32];
	volatile uint32_t EVENTS_IN[8];
	volatile uint32_t RESERVED4[23];
	volatile uint32_t EVENTS_PORT;
	volatile uint32_t RESERVED5[97];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED3[129];
	volatile uint32_t CONFIG[8];
} NRF_GPIOTE_REG;

#endif