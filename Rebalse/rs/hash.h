#ifndef HASH_H
#define HASH_H
#include <stdlib.h>
#include <string.h>
#define MRS 10

//comun a todos los rebalses

int hash(char code[], int M){
    int longitud, i;
    int contador = 0;
    longitud = strlen(code);
    for(i=0; i<longitud; i++){
        contador+=((int)code[i])*(i+1);
    }
    return contador%M;
}

#endif
