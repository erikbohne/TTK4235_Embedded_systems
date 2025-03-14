#pragma once

/**
 * @file elevio.h
 * @brief Hardware interface for elevator control
 *
 * This module provides functions to interface with the elevator hardware,
 * including controlling motors, buttons, lamps, and reading sensors.
 */

/** @brief Number of floors in the elevator system */
#define N_FLOORS 4

/**
 * @brief Enumeration for elevator motor direction
 */
typedef enum { 
    DIRN_DOWN   = -1,  /**< Move elevator down */
    DIRN_STOP   = 0,   /**< Stop elevator */
    DIRN_UP     = 1    /**< Move elevator up */
} MotorDirection;

/** @brief Number of button types per floor */
#define N_BUTTONS 3

/**
 * @brief Enumeration for elevator button types
 */
typedef enum { 
    BUTTON_HALL_UP      = 0,  /**< Hall button for requesting up */
    BUTTON_HALL_DOWN    = 1,  /**< Hall button for requesting down */
    BUTTON_CAB          = 2   /**< Cab button for requesting specific floor */
} ButtonType;

/**
 * @brief Initialize elevator hardware interface
 * 
 * Must be called once before other functions can be used.
 * Establishes connection with the elevator server.
 */
void elevio_init(void);

/**
 * @brief Set motor direction
 * 
 * @param dirn Direction to move (-1:down, 0:stop, 1:up)
 */
void elevio_motorDirection(MotorDirection dirn);

/**
 * @brief Set button lamp state
 * 
 * @param floor Floor number (0-indexed)
 * @param button Button type (hall up, hall down, or cab)
 * @param value 0 to turn off, 1 to turn on
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
 * @brief Set floor indicator lamp
 * 
 * @param floor Floor to indicate (0-indexed)
 */
void elevio_floorIndicator(int floor);

/**
 * @brief Set door open lamp state
 * 
 * @param value 0 to turn off, 1 to turn on
 */
void elevio_doorOpenLamp(int value);

/**
 * @brief Set stop lamp state
 * 
 * @param value 0 to turn off, 1 to turn on
 */
void elevio_stopLamp(int value);

/**
 * @brief Read state of a call button
 * 
 * @param floor Floor number (0-indexed)
 * @param button Button type
 * @return 1 if button is active, 0 otherwise
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief Read floor sensor
 * 
 * @return Current floor (0-indexed), -1 if between floors
 */
int elevio_floorSensor(void);

/**
 * @brief Read stop button
 * 
 * @return 1 if stop button is active, 0 otherwise
 */
int elevio_stopButton(void);

/**
 * @brief Read obstruction switch
 * 
 * @return 1 if obstruction is active, 0 otherwise
 */
int elevio_obstruction(void);

