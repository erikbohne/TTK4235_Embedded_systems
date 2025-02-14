#include <time.h>

#include "../driver/elevio.h"
#include "modules.h"

/**
* @brief Hei på deg
*/
int elevator_startup() {

    printf("Startup up elevator 3000X-SuperG... \n");

    int floor = elevio_floorSensor();

    if(floor != 0){
        printf("Elevator at no floor, driving downwards... \n");
        elevio_motorDirection(DIRN_DOWN);
    }

    while(1){
        floor = elevio_floorSensor();

        if(floor == 0){
            elevio_motorDirection(DIRN_STOP);
            printf("Elevator is at bottom floor... \n");
            break;
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    printf("Start up complete :) \n");

    return 1;
};