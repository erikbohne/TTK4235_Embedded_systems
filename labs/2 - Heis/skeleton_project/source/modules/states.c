#include "states.h"
#include <stdio.h>
#include <unistd.h>
#include "../driver/elevio.h"
#include "input.h"

void standing_still(state_data *data, int floor) {

    if dir = op
        if check alle etasjer over(alle knapper)
             gåt til btn.cab || btn.opp
        if 
            gåt ned om ikke noe opp, bytt dir

    if dir = ned 
        if check alle etasjer ned
            gåp til de
        if 
            evt gå opp, bytt dir 

    int i;
    // Check if any up hall call or cab call is pressed on floors above the current floor
    for (i = floor + 1; i <= 3; i++) {
        if (data->btnStates[i][BUTTON_HALL_UP] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
            printf("Going up from floor %d to %d\n", floor, i);
            elevio_motorDirection(DIRN_UP);
            data->state = DRIVING_UP;
            return;
        }
    } data->btnStates[i][BUTTON_CAB] == 1
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

