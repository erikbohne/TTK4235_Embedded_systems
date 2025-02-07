#include "calculations.h"

// These functions calculate the heuristic tuning parameters
// for a PID controller according to either the classical
// Ziegler Nichols rule, or the Pessens Integral Rule.
double calculate_P_parameter(System * current_system){
    double P_parameter;
    if(current_system->tuning_method == Classic_Ziegler_Nichols){
        P_parameter = 0.6 * current_system->Ku;
    }
    else{
        P_parameter = 0.7 * current_system->Ku;
    }

    return P_parameter;
}

double calculate_I_parameter(System * current_system){
    double I_parameter;
    if(current_system->tuning_method == Classic_Ziegler_Nichols){
        I_parameter = 0.5 * current_system->Tu;
    }
    else{
        I_parameter = 0.4 * current_system->Tu;
    }

    return I_parameter;
}

double calculate_D_parameter(System * current_system){
    double D_parameter;
    if(current_system->tuning_method == Classic_Ziegler_Nichols){
        D_parameter = 0.125 * current_system->Tu;
    }
    else{
        D_parameter = 0.15 * current_system->Tu;
    }

    return D_parameter;
}