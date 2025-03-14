#pragma once

/**
 * @file input.h
 * @brief Button input handling for elevator control
 *
 * This module provides functions to handle user input from elevator buttons,
 * including hall calls and cab calls.
 */

/**
 * @brief Check for button input and update state accordingly
 *
 * Polls all elevator buttons and updates the state data when buttons are pressed.
 * Ignores inputs when the stop button is pressed.
 *
 * @param data Pointer to state data structure
 */
void checkForInput(state_data *data);

/**
 * @brief Turn off button lamps for a specific floor
 *
 * Clears the button states and turns off the corresponding button lamps
 * when an order for a specific floor has been serviced.
 *
 * @param data Pointer to state data structure
 * @param floor The floor where the order has been serviced
 */
void turnOffButtonLamps(state_data *data, int floor);