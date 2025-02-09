#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool* cadeira;  
    int quantidade; 
    int min; 
} SeatManager;

SeatManager* seatManagerCreate(int n) {
    SeatManager* obj = (SeatManager*)malloc(sizeof(SeatManager));
    obj->cadeira = (bool*)calloc(n + 1, sizeof(bool));
    obj->quantidade = n + 1;
    obj->min = 1;
    return obj;
}

int seatManagerReserve(SeatManager* obj) {
    int acento = obj->min;
    obj->cadeira[acento] = true;
    while (obj->min < obj->quantidade && obj->cadeira[obj->min]) {
        obj->min++;
    }
    return acento;
}

void seatManagerUnreserve(SeatManager* obj, int seatNumber) {
    obj->cadeira[seatNumber] = false;
    if (seatNumber < obj->min) {
        obj->min = seatNumber;
    }
}

void seatManagerFree(SeatManager* obj) {
    free(obj->cadeira);
    free(obj);
}

int main() {
    SeatManager* manager = seatManagerCreate(5);
    
    printf("Reservando assentos:\n");
    printf("Assento reservado: %d\n", seatManagerReserve(manager));
    printf("Assento reservado: %d\n", seatManagerReserve(manager));
    printf("Assento reservado: %d\n", seatManagerReserve(manager));
    
    printf("Liberando o assento 2\n");
    seatManagerUnreserve(manager, 2);
    
    printf("Reservando novamente:\n");
    printf("Assento reservado: %d\n", seatManagerReserve(manager));
    printf("Assento reservado: %d\n", seatManagerReserve(manager));
    
    seatManagerFree(manager);
    return 0;
}
