#include "states.h"
#include "../driver/elevio.h"

void standing_still(int btnStates[4][3], state_data *data, int floor){
    if(btnStates[3][1] == 1){
        btnStates[3][1] = 0;
        printf("Going up\n");
        elevio_motorDirection(DIRN_UP);
        data->state = DRIVING_UP;
    }
    if(btnStates[0][0] == 1){
        btnStates[0][0] = 0;
        printf("Going down\n");
        elevio_motorDirection(DIRN_DOWN);
        data->state = DRIVING_DOWN;
    }
}

void driving_up(int btnStates[4][3], state_data *data, int floor){
    if(floor == 3){
        printf("Stopping going up\n");
        elevio_motorDirection(DIRN_STOP);
        data->state = STANDING_STILL;
    }
}

void driving_down(int btnStates[4][3], state_data *data, int floor){
    if(floor == 0){
        printf("Stopping going down\n");
        elevio_motorDirection(DIRN_STOP);
        data->state = STANDING_STILL;
    }
}

