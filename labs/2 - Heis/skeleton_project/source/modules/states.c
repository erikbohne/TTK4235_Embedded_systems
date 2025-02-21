#include "states.h"
#include <stdio.h>
#include <unistd.h>
#include "../driver/elevio.h"
#include "input.h"

void standing_still(state_data *data, int floor) {
    int i;
    // Check if any up hall call or cab call is pressed on floors above the current floor
    for (i = floor + 1; i <= 3; i++) {
        if (data->btnStates[i][BUTTON_HALL_UP] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
            data->btnStates[i][BUTTON_HALL_UP] = 0;
            data->btnStates[i][BUTTON_CAB] = 0;
            printf("Going up from floor %d to %d\n", floor, i);
            elevio_motorDirection(DIRN_UP);
            data->state = DRIVING_UP;
            return;
        }
    }
    // Check if any down hall call or cab call is pressed on floors below the current floor
    for (i = floor - 1; i >= 0; i--) {
        if (data->btnStates[i][BUTTON_HALL_DOWN] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
            data->btnStates[i][BUTTON_HALL_DOWN] = 0;
            data->btnStates[i][BUTTON_CAB] = 0;
            printf("Going down from floor %d to %d\n", floor, i);
            elevio_motorDirection(DIRN_DOWN);
            data->state = DRIVING_DOWN;
            return;
        }
    }
}

void open_door(state_data *data){
    printf("Opening door\n");
    elevio_doorOpenLamp(1);
    sleep(3);
    elevio_doorOpenLamp(0);
    printf("Closing door\n");
}

void driving_up(state_data *data, int floor){

    if (floor >= 0){
        if(data->btnStates[floor][BUTTON_HALL_UP] == 1){
            data->btnStates[floor][BUTTON_HALL_UP] = 0;
            printf("Stopped at floor %d\n", floor);
            elevio_motorDirection(DIRN_STOP);
            turnOffButtonLamps(data, floor);
            open_door(data);
            data->state = STANDING_STILL;
        }
    }

    if(floor == 3){
        printf("Stopping going up\n");
        elevio_motorDirection(DIRN_STOP);
        turnOffButtonLamps(data, floor);
        data->state = STANDING_STILL;
    }
}

void driving_down(state_data *data, int floor){
    if(floor >= 0){
        if(data->btnStates[floor][BUTTON_HALL_DOWN] == 1){
            data->btnStates[floor][BUTTON_HALL_DOWN] = 0;
            printf("Stopped at floor %d\n", floor);
            elevio_motorDirection(DIRN_STOP);
            turnOffButtonLamps(data, floor);
            open_door(data);
            data->state = STANDING_STILL;
            return;
        }
    }
    if(floor == 0){
        printf("Stopping going down\n");
        elevio_motorDirection(DIRN_STOP);
        turnOffButtonLamps(data, floor);
        data->state = STANDING_STILL;
    }
}

