#include "system.h"
#include <stdlib.h>
#include <string.h>

// This function creates a new system object on the heap.
System * system_create(double Ku, double Tu, Tuning tuning_method){
    // First we dynamically allocate a new system
    System * system_new = (System *)malloc(sizeof(System));

    // Then we "construct" the system object.
    system_new->Ku = Ku;
    system_new->Tu = Tu;
    system_new->tuning_method = tuning_method;

    // Finally we return a pointer to the newly created system object.
    return system_new;
}

// This function relinquishes the memory of a system object
void system_delete(System * system_current){
    // Free the current system
    free(system_current);
}
