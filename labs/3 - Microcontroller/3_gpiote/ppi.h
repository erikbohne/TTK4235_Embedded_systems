#ifndef PPI_H
#define PPI_H
#include <stdint.h>

#define PPI ((NRF_PPI_REG*)0x4001F000)

typedef struct {
	uint32_t EN;
	uint32_t DIS;
} PPI_TASKS_TYPE;

typedef struct {
	uint32_t EEP;
	uint32_t TEP;
} PPI_CHANNEL_TYPE;

typedef struct {
	// Tasks
	volatile PPI_TASKS_TYPE PPI_TASKS[4];
	// Registers
	volatile uint32_t RESERVED0[312];
	volatile uint32_t CHEN;
	volatile uint32_t CHENSET;
	volatile uint32_t CHENCLR;
	volatile uint32_t RESERVED1;
	volatile PPI_CHANNEL_TYPE PPI_CH[16];
	volatile uint32_t RESERVED2[156];
	volatile uint32_t CHG[4];
} NRF_PPI_REG;

#endif
