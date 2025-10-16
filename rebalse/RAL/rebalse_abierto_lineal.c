#include <stdio.h>
#include <stdlib.h>
#include "RAL.h"

void llenarEstructura(int set[], RAL *ral, int N){
  int exito;
  printf("N = %d\n", N);
  for(int i=0; i<N; i++){
    exito = alta_RAL(ral, set[i]);
    if(exito) printf("Se cargo el numero %d\n", set[i]);
    else printf("No se pudo cargar el numero %d\n");
  }
}

int main(){
  RAL ral;
  int X[] = {1, 5, 3, 8, 7, 32, 89, 10, 2, 25};
  int N = sizeof(X)/sizeof(int);
  printf("Arreglo:\n[ ");
  for(int i=0; i<N; i++){
    printf("%d", X[i]);
    if(i<N-1) printf(" | ");
  }
  printf(" ]\n");
  init_RAL(&ral);
  llenarEstructura(X, &ral, N);
  mostrar_RAL(ral);
  return 0;
}


//nasheeee anda
