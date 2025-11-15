#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int main(){
  ABB arbol;
  initABB(&arbol);
  int costo = 0;
  float X[] = {80,75,29,4,11,6,23,2,18,24};
  int n = 10;
  printf("insercion\n");
  int exito;
  for(int i=0; i<n; i++){
    costo = 0;
    printf("i=%d, x = %d\n",i, X[i]);
    exito = altaABB(&arbol, X[i]);
    printf("exito: %d\n",exito);
  }
  printf("muestra\nraiz=%d\n\n", arbol.raiz->valor);
  inOrden(arbol.raiz);

  printf("\ncostos de exito a posteriori:\n[ ");
  int costos[10] = {0,0,0,0,0,0,0,0,0,0};
  for(int i=0; i<n; i++){
    arbol.cursor = arbol.raiz;
    arbol.aux = NULL;
    localizarABB(&arbol, X[i], &costos[i]); 
    printf("%d ", costos[i]);
  }

  float X_frac[] = {81, 76, 30, 1, 3, 5, 7, 12, 19, 23.5, 24};
  
  printf("]\n\ncostos de fracaso a posteriori:\n[ ");
  int costos_frac[11] = {0,0,0,0,0,0,0,0,0,0,0};
  for(int i=0; i<11; i++){
    arbol.cursor = arbol.raiz;
    arbol.aux = NULL;
    localizarABB(&arbol, X_frac[i], &costos_frac[i]);
    printf("%d ", costos_frac[i]);
  }
  printf("]\n\n"); 

  treeprint(arbol.raiz, 0);
  return 0;
}
