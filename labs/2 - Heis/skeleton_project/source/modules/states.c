#include "states.h"
#include <stdio.h>
#include "../driver/elevio.h"

void standing_still(state_data *data, int floor){
    if(data->btnStates[3][1] == 1){
        data->btnStates[3][1] = 0;
        printf("Going up\n");
        elevio_motorDirection(DIRN_UP);
        data->state = DRIVING_UP;
    }
    if(data->btnStates[0][0] == 1){
        data->btnStates[0][0] = 0;
        printf("Going down\n");
        elevio_motorDirection(DIRN_DOWN);
        data->state = DRIVING_DOWN;
    }
}

void driving_up(state_data *data, int floor){
    if(floor == 3){
        printf("Stopping going up\n");
        elevio_motorDirection(DIRN_STOP);
        data->state = STANDING_STILL;
    }
}

void driving_down(state_data *data, int floor){
    if(floor == 0){
        printf("Stopping going down\n");
        elevio_motorDirection(DIRN_STOP);
        data->state = STANDING_STILL;
    }
}

