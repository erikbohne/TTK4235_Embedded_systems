#ifndef CALCULATIONS_H
#define CALCUATIONS_H
#include "system.h"

/**
 * @brief This function calculates the P parameter for a given system.
 * 
 * @param[in] current_system The system object to calculate the P parameter for
 * 
 * @return The calculated P parameter
 */
double calculate_P_parameter(System * current_system);

/**
 * @brief This function calculates the I parameter for a given system.
 * 
 * @param[in] current_system The system object to calculate the I parameter for
 * 
 * @return The calculated I parameter
 */
double calculate_I_parameter(System * current_system);

/**
 * @brief This function calculates the D parameter for a given system.
 * 
 * @param[in] current_system The system object to calculate the D parameter for
 * 
 * @return The calculated D parameter
 */
double calculate_D_parameter(System * current_system);

#endif
