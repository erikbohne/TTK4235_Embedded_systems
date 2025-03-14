#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "modules/states.h"
#include "driver/elevio.h"
#include "modules/startup.h"
#include "modules/input.h"


int main(){
    elevio_init();
    

    state_data sData = {STANDING_STILL, {{0,0,0},{0,0,0},{0,0,0},{0,0,0}}, CURRENT_DIR_DOWN};
    int floor = -1;

    printf("State: %u \n\n", sData.state);

    elevator_startup();

    while(1){
        floor = elevio_floorSensor();
        if(floor >= 0){
            elevio_floorIndicator(floor);
        }
        
        // Check for obstruction first - this has highest priority
        if (check_obstruction(&sData, floor)) {
            // If obstruction is active, continue to next iteration
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
            continue;
        }
        
        checkForInput(&sData);

 
        //State machine.
        switch (sData.state) {

        case STANDING_STILL:
            standing_still(&sData, floor);
            break;

        case DRIVING_UP:
            driving(&sData, floor, DIRN_UP);
            break;

        case DRIVING_DOWN:
            driving(&sData, floor, DIRN_DOWN);
            break;
            
        case DOOR_OPEN:
            door_open_state(&sData, floor);
            break;

        default:
            printf("ERROR: Invalid state. ");
            return -1;
            break;
        }
       
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);

    }
    return 0;
}
