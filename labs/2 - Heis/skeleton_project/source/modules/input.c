#include <stdio.h>
#include "../driver/elevio.h"

int getNextUp(int buttons[4][3], int current){
    for(int f = current; f < N_FLOORS; f++){
        if(buttons[f][BUTTON_HALL_UP] == 1){
            return f;
            }
           
        }
    printf("Up miss");
    return -1;
}   

int getNextDown(int buttons[4][3], int current){
    for(int f = current; f > 0; f--){
        if(buttons[f][BUTTON_HALL_DOWN] == 1){
            return f;
            }
        }
    printf("Down miss");
    return -1;
}