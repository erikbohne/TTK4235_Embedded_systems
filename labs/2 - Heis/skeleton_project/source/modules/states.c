#include "states.h"
#include "../driver/elevio.h"

void standing_still(state_data *data, int floor){
    if(sData->btnStates[3][1] == 1){
        sData->btnStates[3][1] = 0;
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

void driving_up(state_data *data, int floor){
    if(data->floor == 3){
        printf("Stopping going up\n");
        elevio_motorDirection(DIRN_STOP);
        data->state = STANDING_STILL;
    }
}

void driving_down(state_data *data, int floor){
    if(data.floor == 0){
        printf("Stopping going down\n");
        elevio_motorDirection(DIRN_STOP);
        data->state = STANDING_STILL;
    }
}

