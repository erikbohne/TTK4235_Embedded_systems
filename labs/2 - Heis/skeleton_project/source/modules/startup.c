#include <time.h>
#include <stdio.h>

#include "../driver/elevio.h"
#include "startup.h"

/**
* @brief Initialize the elevator at startup by moving to a defined position
* Ignores all orders and the stop button during initialization
* @return 1 when initialization is complete
*/
int elevator_startup() {
    printf("Starting up elevator 3000X-SuperG... \n");

    int floor = elevio_floorSensor();

    // Clear all button lamps
    clear_buttons();

    // Check if we're already at a valid floor
    if (floor >= 0) {
        printf("Elevator is already at floor %d\n", floor);
        elevio_floorIndicator(floor);
        printf("Startup complete :) \n");
        return 1;
    }

    // If we're not at a valid floor, drive down to find one
    printf("Elevator not at a defined floor, driving downwards... \n");
    elevio_motorDirection(DIRN_DOWN);

    while (1) {
        // Ignore button presses during initialization
        for (int f = 0; f < N_FLOORS; f++) {
            for (int b = 0; b < N_BUTTONS; b++) {
                if (elevio_callButton(f, b)) {
                    // Ignore button press, do not set button lamp
                    printf("Ignoring button press during initialization\n");
                }
            }
        }

        // Ignore stop button during initialization
        if (elevio_stopButton()) {
            printf("Ignoring stop button during initialization\n");
        }

        floor = elevio_floorSensor();
        if (floor >= 0) {
            elevio_motorDirection(DIRN_STOP);
            elevio_floorIndicator(floor);
            printf("Elevator is at floor %d\n", floor);
            break;
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    printf("Startup complete :) \n");
    return 1;
};

void clear_buttons(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
}

