#pragma once


typedef enum { 
    DOOR_OPEN = 0,
    STANDING_STILL = 1,
    DRIVING_UP = 2,
    DRIVING_DOWN = 3
} State;


int elevator_startup();
void clear_buttons();