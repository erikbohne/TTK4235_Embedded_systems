#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "con_load.h"

static int sockfd;
static pthread_mutex_t sockmtx;

void elevio_init(void){
    char ip[16] = "localhost";
    char port[8] = "15657";
    con_load("elevio.con",
        con_val("com_ip",   ip,   "%s")
        con_val("com_port", port, "%s")
    )
    
    pthread_mutex_init(&sockmtx, NULL);
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1 && "Unable to set up socket");
    
    struct addrinfo hints = {
        .ai_family      = AF_INET, 
        .ai_socktype    = SOCK_STREAM, 
        .ai_protocol    = IPPROTO_TCP,
    };
    struct addrinfo* res;
    getaddrinfo(ip, port, &hints, &res);
    
    int fail = connect(sockfd, res->ai_addr, res->ai_addrlen);
    assert(fail == 0 && "Unable to connect to elevator server");
    
    freeaddrinfo(res);
    
    send(sockfd, (char[4]){0}, 4, 0);
}




void elevio_motorDirection(MotorDirection dirn){
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){1, dirn}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void elevio_buttonLamp(int floor, ButtonType button, int value){
    assert(floor >= 0);
    assert(floor < N_FLOORS);
    assert(button >= 0);
    assert(button < N_BUTTONS);

    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){2, button, floor, value}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void elevio_floorIndicator(int floor){
    assert(floor >= 0);
    assert(floor < N_FLOORS);

    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){3, floor}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void elevio_doorOpenLamp(int value){
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){4, value}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}


void elevio_stopLamp(int value){
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){5, value}, 4, 0);
    pthread_mutex_unlock(&sockmtx);
}




int elevio_callButton(int floor, ButtonType button){
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){6, button, floor}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1];
}


int elevio_floorSensor(void){
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){7}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1] ? buf[2] : -1;
}


int elevio_stopButton(void){
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){8}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1];
}


int elevio_obstruction(void){
    pthread_mutex_lock(&sockmtx);
    send(sockfd, (char[4]){9}, 4, 0);
    char buf[4];
    recv(sockfd, buf, 4, 0);
    pthread_mutex_unlock(&sockmtx);
    return buf[1];
}
