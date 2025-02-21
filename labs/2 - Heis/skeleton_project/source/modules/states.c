#include "states.h"
#include <stdio.h>
#include <unistd.h>
#include "../driver/elevio.h"
#include "input.h"

void standing_still(state_data *data, int floor) {
    int i;

    // Prefer the direction from the last ride, if available.
    if (data->dir == CURRENT_DIR_UP) {
        // Look for any orders above the current floor.
        for (i = floor + 1; i < 4; i++) {
            if (data->btnStates[i][BUTTON_HALL_UP] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Going up from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_UP);
                data->state = DRIVING_UP;
                return;
            }
        }
        // If no orders above, see if there are any down orders.
        for (i = floor - 1; i >= 0; i--) {
            if (data->btnStates[i][BUTTON_HALL_DOWN] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Changing direction to down from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_DOWN);
                data->state = DRIVING_DOWN;
                data->dir = CURRENT_DIR_DOWN;
                return;
            }
        }
    } else if (data->dir == CURRENT_DIR_DOWN) {
        // Look for any orders below the current floor.
        for (i = floor - 1; i >= 0; i--) {
            if (data->btnStates[i][BUTTON_HALL_DOWN] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Going down from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_DOWN);
                data->state = DRIVING_DOWN;
                return;
            }
        }
        // If no orders below, check for orders above.
        for (i = floor + 1; i < 4; i++) {
            if (data->btnStates[i][BUTTON_HALL_UP] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Changing direction to up from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_UP);
                data->state = DRIVING_UP;
                data->dir = CURRENT_DIR_DOWN;
                return;
            }
        }
    } else {
        // No previous direction: default to checking up first.
        for (i = floor + 1; i < 4; i++) {
            if (data->btnStates[i][BUTTON_HALL_UP] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Going up from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_UP);
                data->state = DRIVING_UP;
                data->dir = CURRENT_DIR_UP;
                return;
            }
        }
        // Then check downwards.
        for (i = floor - 1; i >= 0; i--) {
            if (data->btnStates[i][BUTTON_HALL_DOWN] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Going down from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_DOWN);
                data->state = DRIVING_DOWN;
                data->dir = CURRENT_DIR_DOWN;
                return;
            }
        }
    }

    // If no orders are pending, close the door and remain idle.
    elevio_doorOpenLamp(0);
    printf("Closing door and remaining idle at floor %d\n", floor);
}

void open_door(state_data *data) {
    elevio_doorOpenLamp(1);
    printf("Opening door\n");
    sleep(3);
    elevio_doorOpenLamp(0);
    printf("Closing door\n");
}

void driving_up(state_data *data, int floor){

    if (floor >= 0){
        if(data->btnStates[floor][BUTTON_HALL_UP] == 1 || data->btnStates[floor][BUTTON_CAB] == 1){
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
        if(data->btnStates[floor][BUTTON_HALL_DOWN] == 1 || data->btnStates[floor][BUTTON_CAB] == 1){
            printf("Stopped at floor %d\n", floor + 1);
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

