#pragma once

/**
 * @file startup.h
 * @brief Elevator initialization and startup procedures
 *
 * This module handles the elevator initialization sequence, ensuring
 * the elevator is at a known floor position on startup and all button
 * lamps are cleared.
 */

/**
 * @brief Initialize the elevator on startup
 *
 * Performs the elevator startup sequence:
 * 1. Clears all button lamps
 * 2. Moves the elevator to a defined floor position if it's between floors
 * 3. Sets the elevator to a known initial state
 *
 * @return Initial floor position after startup is complete
 */
int elevator_startup();

/**
 * @brief Clear all button lamps
 *
 * Turns off all button lamps to ensure a clean state on startup.
 */
void clear_buttons();