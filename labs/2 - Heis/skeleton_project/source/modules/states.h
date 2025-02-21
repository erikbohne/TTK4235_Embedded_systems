#pragma once

typedef enum { 
    DOOR_OPEN = 0,
    STANDING_STILL = 1,
    DRIVING_UP = 2,
    DRIVING_DOWN = 3
} State;

struct state_data{
    State state;
};

void standing_still(int btnStates[4][3], state_data);
void driving_up(int btnStates[4][3],state_data );
void driving_down(int btnStates[4][3] ,state_data);