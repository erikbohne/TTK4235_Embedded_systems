#ifndef SYSTEM_H
#define SYSTEM_H

typedef enum {
    Classic_Ziegler_Nichols,
    Pessen_Integral_Rule
} Tuning;

/**
 * @brief A structure to represent a system and desired PID tuning method.
 */
typedef struct {
    double Ku;            /** < The gain margin for loop stability */
    double Tu;            /** < The period of the oscillations frequency at the stability limit */
    Tuning tuning_method; /** < The desired PID tuning method */
} System;


// Document this
System * system_create(double Ku, double Tu, Tuning tuning_method);

// Document this
void system_delete(System * system_current);

#endif
