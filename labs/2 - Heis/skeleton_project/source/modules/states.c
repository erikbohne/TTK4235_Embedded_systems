#include "states.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../driver/elevio.h"
#include "input.h"

// Variables to track door timing
static time_t door_opened_time = 0;
static int door_timer_active = 0;
static int obstruction_active = 0;
static int idle_message_printed = 0; // Track if idle message was already printed

// Clear all orders and turn off all button lights
void clear_all_orders(state_data *data) {
    printf("Clearing all orders\n");
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            data->btnStates[f][b] = 0;
            elevio_buttonLamp(f, b, 0);
        }
    }
}

void standing_still(state_data *data, int floor) {
    int i;

    // Check for stop button
    if (elevio_stopButton()) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        clear_all_orders(data);
        
        // If at a floor, open the door
        if (floor >= 0) {
            elevio_doorOpenLamp(1);
            door_opened_time = time(NULL);
            door_timer_active = 1;
            data->state = DOOR_OPEN;
        }
        
        printf("STOP button pressed. Elevator stopped.\n");
        
        // Wait until stop button is released
        while (elevio_stopButton()) {
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        
        elevio_stopLamp(0);
        printf("STOP button released.\n");
        return;
    }

    // Check if there are any orders at the current floor
    if (floor >= 0 && (data->btnStates[floor][BUTTON_HALL_UP] || data->btnStates[floor][BUTTON_HALL_DOWN] || data->btnStates[floor][BUTTON_CAB])) {
        data->state = DOOR_OPEN;
        turnOffButtonLamps(data, floor);
        elevio_doorOpenLamp(1);
        door_opened_time = time(NULL);
        door_timer_active = 1;
        idle_message_printed = 0; // Reset idle message flag when state changes
        printf("Opening door at floor %d for existing order\n", floor);
        return;
    }

    // Prefer the direction from the last ride, if available.
    if (data->dir == CURRENT_DIR_UP) {
        // Look for any orders above the current floor.
        for (i = floor + 1; i < N_FLOORS; i++) {
            if (data->btnStates[i][BUTTON_HALL_UP] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Going up from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_UP);
                data->state = DRIVING_UP;
                idle_message_printed = 0; // Reset idle message flag
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
        for (i = floor + 1; i < N_FLOORS; i++) {
            if (data->btnStates[i][BUTTON_HALL_UP] == 1 || data->btnStates[i][BUTTON_CAB] == 1) {
                printf("Changing direction to up from floor %d to %d\n", floor, i);
                elevio_motorDirection(DIRN_UP);
                data->state = DRIVING_UP;
                data->dir = CURRENT_DIR_UP;  // Fixed: Should be UP not DOWN
                return;
            }
        }
    } else {
        // No previous direction: default to checking up first.
        for (i = floor + 1; i < N_FLOORS; i++) {
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
    if (!idle_message_printed) {
        printf("No orders pending, remaining idle at floor %d\n", floor);
        idle_message_printed = 1;
    }
}


void door_open_state(state_data *data, int floor) {
    // Check for stop button
    if (elevio_stopButton()) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        clear_all_orders(data);
        printf("STOP button pressed while door open. Keeping door open.\n");
        
        // Wait until stop button is released
        while (elevio_stopButton()) {
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        
        elevio_stopLamp(0);
        printf("STOP button released. Resetting door timer.\n");
        
        // Reset door timer
        door_opened_time = time(NULL);
        return;
    }

    // Check for obstruction
    if (elevio_obstruction()) {
        if (!obstruction_active) {
            printf("Obstruction detected, keeping door open\n");
            obstruction_active = 1;
        }
        door_opened_time = time(NULL); // Reset timer
        return;
    } else if (obstruction_active) {
        printf("Obstruction cleared, starting door timer\n");
        obstruction_active = 0;
        door_opened_time = time(NULL); // Reset timer
    }

    // Check if door timer has expired
    if (door_timer_active && time(NULL) - door_opened_time >= 3) {
        printf("Door timer expired, closing door\n");
        elevio_doorOpenLamp(0);
        door_timer_active = 0;
        data->state = STANDING_STILL;
        idle_message_printed = 0; // Reset the flag to allow one idle message after closing door
    }
}

void door_open_state(state_data *data, int floor) {
    // Check for stop button
    if (elevio_stopButton()) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        clear_all_orders(data);
        printf("STOP button pressed while door open. Keeping door open.\n");
        
        // Wait until stop button is released
        while (elevio_stopButton()) {
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        
        elevio_stopLamp(0);
        printf("STOP button released. Resetting door timer.\n");
        
        // Reset door timer
        door_opened_time = time(NULL);
        return;
    }

    // Check for obstruction
    if (elevio_obstruction()) {
        if (!obstruction_active) {
            printf("Obstruction detected, keeping door open\n");
            obstruction_active = 1;
        }
        door_opened_time = time(NULL); // Reset timer
        return;
    } else if (obstruction_active) {
        printf("Obstruction cleared, starting door timer\n");
        obstruction_active = 0;
        door_opened_time = time(NULL); // Reset timer
    }

    // Check if door timer has expired
    if (door_timer_active && time(NULL) - door_opened_time >= 3) {
        printf("Door timer expired, closing door\n");
        elevio_doorOpenLamp(0);
        door_timer_active = 0;
        data->state = STANDING_STILL;
        idle_message_printed = 0; // Reset the flag to allow one idle message after closing door
    }
}

void driving_up(state_data *data, int floor){
    // Check for stop button
    if (elevio_stopButton()) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        clear_all_orders(data);
        
        printf("STOP button pressed while moving up. Elevator stopped.\n");
        
        // Wait until stop button is released
        while (elevio_stopButton()) {
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        
        elevio_stopLamp(0);
        printf("STOP button released.\n");
        data->state = STANDING_STILL;
        return;
    }

    if (floor >= 0){
        // Check if we need to stop at this floor
        if (data->btnStates[floor][BUTTON_HALL_UP] == 1 || data->btnStates[floor][BUTTON_CAB] == 1) {
            printf("Stopped at floor %d\n", floor);
            elevio_motorDirection(DIRN_STOP);
            turnOffButtonLamps(data, floor);
            elevio_doorOpenLamp(1);
            door_opened_time = time(NULL);
            door_timer_active = 1;
            data->state = DOOR_OPEN;
        }
    }

    // Safety check for top floor
    if (floor == N_FLOORS - 1) {
        printf("Reached top floor, stopping\n");
        elevio_motorDirection(DIRN_STOP);
        turnOffButtonLamps(data, floor);
        elevio_doorOpenLamp(1);
        door_opened_time = time(NULL);
        door_timer_active = 1;
        data->state = DOOR_OPEN;
    }
}

void driving_down(state_data *data, int floor){
    // Check for stop button
    if (elevio_stopButton()) {
        elevio_motorDirection(DIRN_STOP);
        elevio_stopLamp(1);
        clear_all_orders(data);
        
        printf("STOP button pressed while moving down. Elevator stopped.\n");
        
        // Wait until stop button is released
        while (elevio_stopButton()) {
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        
        elevio_stopLamp(0);
        printf("STOP button released.\n");
        data->state = STANDING_STILL;
        return;
    }

    if (floor >= 0){
        // Check if we need to stop at this floor
        if (data->btnStates[floor][BUTTON_HALL_DOWN] == 1 || data->btnStates[floor][BUTTON_CAB] == 1) {
            printf("Stopped at floor %d\n", floor);
            elevio_motorDirection(DIRN_STOP);
            turnOffButtonLamps(data, floor);
            elevio_doorOpenLamp(1);
            door_opened_time = time(NULL);
            door_timer_active = 1;
            data->state = DOOR_OPEN;
            return;
        }
    }
    
    // Safety check for bottom floor
    if (floor == 0) {
        printf("Reached bottom floor, stopping\n");
        elevio_motorDirection(DIRN_STOP);
        turnOffButtonLamps(data, floor);
        elevio_doorOpenLamp(1);
        door_opened_time = time(NULL);
        door_timer_active = 1;
        data->state = DOOR_OPEN;
    }
}

