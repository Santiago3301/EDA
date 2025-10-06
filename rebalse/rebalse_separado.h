#ifndef REBALSE_SEPARADO_H
#define REBALSE_SEPARADO_H
#include <malloc.h>
#include <string.h>
#include "estudiante.h"

#define M 50

typedef struct n{
    Estudiante e;
    struct n* next;
}nodo;

typedef struct{
    nodo* tabla[M];
    int ult;
    nodo* cur;
    nodo* aux;
}rebalse_separado;

void init_RS(rebalse_separado *r){
    r->ult = -1;

    for(int i=0; i<M; i++){
        r->tabla[i] =  NULL;
    }
}

int hash(char code[]){
    int longitud, i;
    int contador = 0;
    longitud = strlen(code);
    for(i=0; i<longitud; i++){
        contador+=((int)code[i])*(i+1);
    }
    return contador%M;
}

void localizar_RS(rebalse_separado *r, char code[], int *exito){
    printf("buscando\n");
    int index = hash(code);
    r->cur = r->tabla[index];
    while(r->cur != NULL){
        if(strcmp(r->cur->e.codigo, code) == 0) break;
        else{
            r->aux = r->cur;
            r->cur = r->cur->next;
        }
        
        
    }
    if(r->cur == NULL) *exito = 0;
    else *exito = 1;
}

void alta_RS(rebalse_separado *r, Estudiante e, int *exito, int *cant){
    localizar_RS(r,e.codigo,exito);
    if(*exito){
        *exito = 0; //repetido
        printf("repetido\n");
    }   
    else{
        printf("cargando\n");
        //insertar al inicio de la lista
        nodo* nuevo = (nodo*)malloc(sizeof(nodo));
        printf("%p\n", nuevo);
        if(nuevo == NULL){
            *exito = -1;
            printf("falla de memoria\n");
            return; //falla de memoria
        }
        printf("memoria asignada\n");
        nuevo->e = e;
        nuevo->next = r->tabla[hash(e.codigo)];
        r->tabla[hash(e.codigo)] = nuevo;
        *exito = 1;
        (*cant)++;
        printf("cargado\n");
    }
}

void baja_RS(rebalse_separado *r, Estudiante e, int *exito, int *cant){
    localizar_RS(r,e.codigo,exito);
    if(!(*exito)) printf("no encontrado\n");
    else{
        if(
           //comparación de la nupla 
          ){
            //baja
          } 
    }
}

#endif // REBALSE_SEPARADO_H