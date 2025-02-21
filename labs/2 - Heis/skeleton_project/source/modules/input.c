#include <stdio.h>
#include "../driver/elevio.h"
#include "states.h"

//Setter kun lys på atm. Vi skues av manuelt av heisen når det har håndtert etasjen. 
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

//Ikke i bruk enda
// int getNextUp(int buttons[4][3], int current){
//     for(int f = current; f < N_FLOORS; f++){
//         if(buttons[f][BUTTON_HALL_UP] == 1){
//             return f;
//             }
           
//         }
//     printf("Up miss");
//     return -1;
// }   

// int getNextDown(int buttons[4][3], int current){
//     for(int f = current; f > 0; f--){
//         if(buttons[f][BUTTON_HALL_DOWN] == 1){
//             return f;
//             }
//         }
//     printf("Down miss");
//     return -1;
// }