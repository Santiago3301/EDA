#include <stdio.h>
#include "LSO.h"

int main(){
    Nupla V[5];

    V[0].x = 1;
    V[0].y = 3;
    V[1].x = 2;
    V[1].y = 1;
    V[2].x = 3;
    V[2].y = 5;
    V[3].x = 4;
    V[3].y = 2;
    V[4].x = 5;
    V[4].y = 4;

    int N = 5;

    LSO L;

    init_LSO(&L);
    
    int exito = 0;

    for(int i = 0; i<N; i++){
        alta_LSO(&L, V[i], &exito);
    }

    mostrar_LSO(L);
}