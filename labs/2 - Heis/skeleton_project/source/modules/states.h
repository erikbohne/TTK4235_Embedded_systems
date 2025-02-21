#pragma once

typedef enum { 
    DOOR_OPEN = 0,
    STANDING_STILL = 1,
    DRIVING_UP = 2,
    DRIVING_DOWN = 3
} State;

typedef struct state_data {
    State state;
    int btnStates[4][3];
} state_data;

void standing_still(state_data *data, int floor);
void open_door(state_data *data);
void driving_up(state_data *data, int floor);
void driving_down(state_data *data, int floor);