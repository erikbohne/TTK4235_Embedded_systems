#include "../driver/elevio.h"
#include "modules.h"

/**
* @brief Hei på deg
*/
int elevator_startup() {

    printf("Startup up elevator 3000X-SuperG... \n");

    int floor = elevio_floorSensor();

    printf("Floor found %d", floor);

    return 1;
};