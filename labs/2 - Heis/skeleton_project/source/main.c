#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
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
    

    State state = STANDING_STILL;
    int btnStates[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    int destination = NULL;
    int floor = NULL;

    printf("State: %u \n\n", state);

    elevator_startup();

    while(1){
        floor = elevio_floorSensor();

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnbtnStates = elevio_callButton(f, b);
                if(btnbtnStates){
                    btnStates[f][b] = 1;
                    printf("%d \n",btnStates[f][b]);
                    elevio_buttonLamp(f, b, 1);
                }
            }
        }


        // //Consept state machine
        if(state == STANDING_STILL){

            //Transistion
            if(btnStates[3][1] == 1){
                btnStates[3][1] = 0;
                printf("Going up \n");
                elevio_motorDirection(DIRN_UP);
                state = DRIVING_UP;
            }

            if(btnStates[0][0] == 1){
                btnStates[0][0] = 0;
                printf("Going down \n");
                elevio_motorDirection(DIRN_DOWN);
                state = DRIVING_DOWN;
            }

           
            
        }

        if(state == DRIVING_UP){
            if(floor == 3){
                printf("Stopping going up \n");
                elevio_motorDirection(DIRN_STOP);
                state = STANDING_STILL;
                
            }
        }

        if(state == DRIVING_DOWN){
            if(floor == 0){
                printf("Stopping going down \n");
                elevio_motorDirection(DIRN_STOP);
                state = STANDING_STILL;
                
            }
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