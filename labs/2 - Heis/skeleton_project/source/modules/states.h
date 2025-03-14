#pragma once

/**
 * @file states.h
 * @brief State machine implementation for elevator control
 *
 * This module defines the elevator's state machine, including state enumeration,
 * state data structure, and functions to handle each state's behavior.
 */

/**
 * @brief Enumeration of elevator states
 */
typedef enum { 
    DOOR_OPEN = 0,       /**< Door is open, waiting for timer or obstruction clear */
    STANDING_STILL = 1,  /**< Elevator is idle at a floor */
    DRIVING_UP = 2,      /**< Elevator is moving upward */
    DRIVING_DOWN = 3     /**< Elevator is moving downward */
} State;

/**
 * @brief Enumeration of current direction preference
 */
typedef enum { 
    CURRENT_DIR_UP = 0,    /**< Current direction preference is up */
    CURRENT_DIR_DOWN = 1,  /**< Current direction preference is down */
} Direction;

/**
 * @brief Structure to hold elevator state data
 */
typedef struct state_data {
    State state;           /**< Current elevator state */
    int btnStates[4][3];   /**< Button press states for all floors and button types */
    Direction dir;         /**< Current direction preference */
} state_data;

/**
 * @brief Handle idle state when elevator is standing still at a floor
 *
 * Checks for button presses and decides whether to service orders by 
 * moving up, down, or opening doors.
 *
 * @param data Pointer to state data structure
 * @param floor Current floor (-1 if between floors)
 */
void standing_still(state_data *data, int floor);

/**
 * @brief Simple door open/close sequence
 *
 * Opens door, waits, and closes door.
 *
 * @param data Pointer to state data structure
 */
void open_door(state_data *data);

/**
 * @brief Handle door open state
 *
 * Manages door timing, obstruction detection, and state transitions 
 * when door is open.
 *
 * @param data Pointer to state data structure
 * @param floor Current floor
 */
void door_open_state(state_data *data, int floor);

/**
 * @brief Handle upward driving state
 *
 * Checks if elevator should stop at current floor based on button presses.
 *
 * @param data Pointer to state data structure
 * @param floor Current floor (-1 if between floors)
 */
void driving_up(state_data *data, int floor);

/**
 * @brief Handle downward driving state
 *
 * Checks if elevator should stop at current floor based on button presses.
 *
 * @param data Pointer to state data structure
 * @param floor Current floor (-1 if between floors)
 */
void driving_down(state_data *data, int floor);

/**
 * @brief Clear all button orders and turn off all button lights
 *
 * @param data Pointer to state data structure
 */
void clear_all_orders(state_data *data);

/**
 * @brief Check for obstruction and handle accordingly
 *
 * When obstruction is detected, stop elevator, clear orders, and open door.
 *
 * @param data Pointer to state data structure
 * @param floor Current floor (-1 if between floors)
 * @return 1 if obstruction is active, 0 otherwise
 */
int check_obstruction(state_data *data, int floor);