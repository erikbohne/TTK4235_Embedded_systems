#include <stdio.h>
#include "../driver/elevio.h"
#include "states.h"

void checkForInput(state_data *data){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int pressed = elevio_callButton(f, b);
            if(pressed){
                data->btnStates[f][b] = 1;
                elevio_buttonLamp(f, b, 1);
            }
        }
    }
}

void turnOffButtonLamps(state_data *data, int floor){
    for(int button = 0; button<3; button++){
        data->btnStates[floor][button] = 0;
        elevio_buttonLamp(floor, button, 0);
    }
}

