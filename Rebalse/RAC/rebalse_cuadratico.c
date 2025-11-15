#include <stdio.h>
#include <stdlib.h>
#include "RAC.h"

void llenarEstructura(int set[], RAC *rac, int N){
  int exito;
  printf("N = %d\n", N);
  for(int i=0; i<N; i++){
    exito = alta_RAC(rac, set[i]);
    if(exito == 1) printf("Se cargo el numero %d\n", set[i]);
    else printf("No se pudo cargar el numero %d\n", set[i]);
  }
}

int main(){
  RAC rac;
  int X[] = {1,8,27,6,125,3,216,49,5,343};
  int N = sizeof(X)/sizeof(int);
  printf("Arreglo:\n[ ");
  for(int i=0; i<N; i++){
    printf("%d", X[i]);
    if(i<N-1) printf(" | ");
  }
  printf(" ]\n");
  init_RAC(&rac);
  llenarEstructura(X, &rac, N);
  mostrar_RAC(rac);
  return 0;
}


