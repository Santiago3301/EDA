#ifndef REBALSE_SEPARADO_H
#define REBALSE_SEPARADO_H
#include <stdlib.h>
#include "hash.h"
#include "estudiante.h"


typedef struct n{
  Estudiante e;
  struct n *next;
}Nodo;

typedef struct{
  Nodo* acc;
}Celda;

void init_RS(Celda rs[], int *cant){
  for(int i=0; i<MRS; i++){
    rs[i].acc = NULL;
  }

}

#endif
