#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "calculations.h"

int main(){
    System * current_system = system_create(12.1, 73.0, Pessen_Integral_Rule);

    double P_parameter, I_parameter, D_parameter;
    const char* tuning_methods[] = {"Classic-Ziegler-Nichols","Pessens Integral Rule"};

    P_parameter = calculate_P_parameter(current_system);
    I_parameter = calculate_I_parameter(current_system);
    D_parameter = calculate_D_parameter(current_system);

    printf("Given Ku = %f and Tu = %f, the optimal PID parameters when using %s are:\nKp = %f, Ki = %f and Kd = %f\n",\
           current_system->Ku,current_system->Tu,tuning_methods[current_system->tuning_method],P_parameter,I_parameter,D_parameter);

    system_delete(current_system);
    return 0;
}
