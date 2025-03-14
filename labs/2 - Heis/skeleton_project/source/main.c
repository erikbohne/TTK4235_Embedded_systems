/**
 * @file main.c
 * @brief Main elevator control program
 *
 * This is the main entry point for the elevator control system.
 * It initializes the elevator hardware, sets up the initial state,
 * and runs the main control loop implementing the state machine.
 *
 * @author [Student Name]
 * @date [Date]
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "modules/states.h"
#include "driver/elevio.h"
#include "modules/startup.h"
#include "modules/input.h"

/**
 * @brief Main entry point for the elevator control program
 *
 * Initializes the elevator hardware, performs startup sequence,
 * and runs the main control loop implementing the elevator state machine.
 *
 * @return 0 on successful execution, -1 on error
 */
int main(){
    // Initialize elevator hardware interface
    elevio_init();
    
    // Initialize state data structure
    state_data sData = {STANDING_STILL, {{0,0,0},{0,0,0},{0,0,0},{0,0,0}}, CURRENT_DIR_DOWN};
    int floor = -1;

    printf("State: %u \n\n", sData.state);

    // Perform elevator startup sequence
    elevator_startup();

    // Main control loop
    while(1){
        // Get current floor
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
        
        // Check for button inputs
        checkForInput(&sData);

        // State machine implementation
        switch (sData.state) {
            case STANDING_STILL:
                standing_still(&sData, floor);
                break;

            case DRIVING_UP:
                driving_up(&sData, floor);
                break;

            case DRIVING_DOWN:
                driving_down(&sData, floor);
                break;
                
            case DOOR_OPEN:
                door_open_state(&sData, floor);
                break;

            default:
                printf("ERROR: Invalid state. ");
                return -1;
        }
       
        // Short delay to prevent CPU hogging
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    
    return 0;
}
