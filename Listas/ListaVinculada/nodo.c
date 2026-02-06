#include <stdlib.h>
#include "nodo.h"

Nodo* crear_nodo(int x){
  Nodo* nuevo = (Nodo *)malloc(sizeof(Nodo));
  if(nuevo == NULL){
    printf("\nMemoria insuficiente");
    return NULL;
  }
  nuevo->valor = x;
  nuevo->sig = NULL;

  return nuevo;
}
