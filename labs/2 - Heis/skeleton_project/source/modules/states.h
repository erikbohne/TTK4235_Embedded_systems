#pragma once

#include "../driver/elevio.h"

typedef enum { 
    DOOR_OPEN = 0,
    STANDING_STILL = 1,
    DRIVING_UP = 2,
    DRIVING_DOWN = 3
} State;

typedef enum { 
    CURRENT_DIR_UP = 0,
    CURRENT_DIR_DOWN = 1,
} Direction;



typedef struct state_data {
    State state;
    int btnStates[4][3];
    Direction dir;
} state_data;

void standing_still(state_data *data, int floor);
void open_door(state_data *data);
void door_open_state(state_data *data, int floor);
void driving(state_data *data, int floor, MotorDirection dir);
void clear_all_orders(state_data *data);
int check_obstruction(state_data *data, int floor);