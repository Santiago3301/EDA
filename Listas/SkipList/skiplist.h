#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_LEVEL 3 
#define WIDTH 8

typedef struct nodoSL{
  int x; //asociante
  int y; //info asociada 
  struct nodoSL* next[MAX_LEVEL+1];
}NodoSL;

typedef struct{
  int nivel; //maximo nivel utilizado
  NodoSL *acc;
}SKIPLIST;

void init_skiplist(SKIPLIST *sl){
  sl->nivel = 0;
  sl->acc = (NodoSL*)malloc(sizeof(NodoSL));
  sl->acc->x = -999999;
  sl->acc->y = -999999;
  
  for(int i=0; i<=MAX_LEVEL; i++){
    sl->acc->next[i] = NULL;
  }
}

void localizar_skiplist(SKIPLIST sl, int x, NodoSL *update[], int *exito){
  for(int i=0; i<=MAX_LEVEL; i++){
    update[i] = sl.acc;
  }
  NodoSL *cur = sl.acc;
  int nivel = sl.nivel;
  for(int i=nivel; i>=0; i--){
    while(cur->next[i] != NULL && cur->next[i]->x < x){
      cur = cur->next[i];
    }
    update[i] = cur;
  }
  cur = cur->next[0];
  if(cur != NULL && cur->x == x){
    *exito = 1;
  }
  else{
    *exito = 0;
  }
}

NodoSL* crear_nodoSL(int x, int y){
  NodoSL *nuevo = (NodoSL *)malloc(sizeof(NodoSL));
  nuevo->x = x;
  nuevo->y = y;

  for(int i=0; i<=MAX_LEVEL; i++)
    nuevo->next[i] = NULL;

  return nuevo;
}

int obtener_nivel(){
  int n = 0;
  while((rand()/(double)RAND_MAX) < 0.5 && n < MAX_LEVEL){
    n++;
  }
  return n;
}

void alta_skiplist(SKIPLIST *sl, int x, int y, int *exito){
  NodoSL* update[MAX_LEVEL+1];
  localizar_skiplist(*sl, x, update, exito);
  if(*exito == 1){
    *exito = 0;
  }
  else{
    NodoSL* nuevo = crear_nodoSL(x, y);
    int nivel = obtener_nivel();
    for(int i=0; i<=nivel; i++){
      nuevo->next[i] = update[i]->next[i];
      update[i]->next[i] = nuevo;
    }

    if(nivel > sl->nivel){
      sl->nivel = nivel;
    }
    
    *exito = 1;
  }
}

int digitos(int x) {
    if (x == 0) return 1;
    int d = 0;
    while (x != 0) {
        x /= 10;
        d++;
    }
    return d;
}

void mostrar_skiplist(SKIPLIST sl){
  NodoSL* cur = sl.acc->next[0];
  NodoSL* nivel0[10];
  int count = 0;
  
  while(cur != NULL){
    nivel0[count] = cur;
    cur = cur->next[0];
    count++;
  }

  for(int i=0; i<=MAX_LEVEL; i++){
    NodoSL *cur = sl.acc->next[i];
    int index = 0;

    printf("[%d]--", i);

    while(index < count){
      if(cur != NULL && cur->x == nivel0[index]->x){
        int x = cur->x;
        printf(">[%d]--", x);
        cur = cur->next[i];
      }else{
        int d = digitos(nivel0[index]->x);
        printf("-----");
        while(d>0){
          printf("-");
          d--;
        }
      }
      index++;
    }

    printf(">[+inf]\n");

  }
}

#endif
