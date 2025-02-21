#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "modules/states.h"
#include "driver/elevio.h"
#include "modules/startup.h"



int getRequestedFloor(int buttons[4][3]){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(buttons[f][b] == 1){
                return f;
            }
        }
    }
    return 0;
}


int main(){
    elevio_init();
    

    state_data sData = {STANDING_STILL, {{0,0,0},{0,0,0},{0,0,0},{0,0,0}}};
    int floor = -1;

    // int destination = NULL;
    // int direction;

    printf("State: %u \n\n", sData.state);

    elevator_startup();

    while(1){
        floor = elevio_floorSensor();
        if(floor >= 0){
            elevio_floorIndicator(floor);
        }
        
        
        //TODO: Test kode. Må over til input.c
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnbtnStates = elevio_callButton(f, b);
                if(btnbtnStates){
                    sData.btnStates[f][b] = 1;
                    elevio_buttonLamp(f, b, 1);
                }
            }
        }

        if(sData.state == STANDING_STILL){
            standing_still(&sData, floor);
        }
        else if(sData.state == DRIVING_UP){
            driving_up(&sData, floor);
        }
        else if(sData.state == DRIVING_DOWN){
            driving_down(&sData, floor);
        }
       
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    // while(1){
    //     int floor = elevio_floorSensor();

    //     if(floor == 0){
    //         elevio_motorDirection(DIRN_UP);
    //     }

    //     if(floor == N_FLOORS-1){
    //         elevio_motorDirection(DIRN_DOWN);
    //     }

    //     for(int f = 0; f < N_FLOORS; f++){
    //         for(int b = 0; b < N_BUTTONS; b++){
    //             int btnbtnStates = elevio_callButton(f, b);
    //             elevio_buttonLamp(f, b, btnbtnStates);
    //         }
    //     }

    //     if(elevio_obstruction()){
    //         elevio_stopLamp(1);
    //     } else {
    //         elevio_stopLamp(0);
    //     }
        
    //     if(elevio_stopButton()){
    //         elevio_moto// int getRequestedFloor(int buttons[4][3]){
//     for(int f = 0; f < N_FLOORS; f++){
//         for(int b = 0; b < N_BUTTONS; b++){
//             if(buttons[f][b] == 1){
//                 return f;
//             }
//         }
//     }
//     return 0;
// }rDirection(DIRN_STOP);
    //         break;
    //     }
        
    //     nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    // }

    return 0;
}


// int getRequestedFloor(int buttons[4][3]){
//     for(int f = 0; f < N_FLOORS; f++){
//         for(int b = 0; b < N_BUTTONS; b++){
//             if(buttons[f][b] == 1){
//                 return f;
//             }
//         }
//     }
//     return 0;
// }// int getRequestedFloor(int buttons[4][3]){
//     for(int f = 0; f < N_FLOORS; f++){
//         for(int b = 0; b < N_BUTTONS; b++){
//             if(buttons[f][b] == 1){
//                 return f;
//             }
//         }
//     }
//     return 0;
// }