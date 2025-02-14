#include "elevio.h"

int main(void){
    elevio_init();

    while(1){
        elevio_motorDirection(DIRN_DOWN);
        while(elevio_floorSensor() != 0){}
        elevio_motorDirection(DIRN_UP);
        while(elevio_floorSensor() != 3){}
    }
}
