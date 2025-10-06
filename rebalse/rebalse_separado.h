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
}rebalse_separado;

void init_RS(rebalse_separado *r){
    r->ult = -1;

    for(int i=0; i<M; i++){
        r->tabla[i] = r->tabla[i]->next =  NULL;
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

void localizar_RS(rebalse_separado r, char code[], int *exito){
    printf("buscando\n");
    int index = hash(code);
    if(r.tabla[index]->next == NULL){
        *exito = 0;
        return; //lista vacia
    }
    else{
        nodo* actual = r.tabla[index]->next;
        while(actual != NULL){
            if(strcmp(actual->e.codigo, code) != 0) actual = actual->next;
        }
        if(actual == NULL) *exito = 0; //llego al final de la estructura (no encontrado)
        else *exito = 1;
    }
}

void alta_RS(rebalse_separado *r, Estudiante e, int *exito, int *cant){
    localizar_RS(*r,e.codigo,exito);
    if(*exito) *exito = 0; //repetido
    else{
        printf("cargando\n");
        //insertar al inicio de la lista
        nodo* nuevo = (nodo*)malloc(sizeof(nodo));
        printf("%p\n", nuevo);
        if(nuevo == NULL){
            *exito = -1;
            return; //falla de memoria
        }
        printf("memoria asignada\n");
        nuevo->e = e;
        printf("lista.cur = %p", r->tabla[hash(e.codigo)]);
        //if(r->tabla[hash(e.codigo)]->next == NULL) printf("lista->next = NULL\n");
        //else printf("lista->next = %p\n", r->tabla[hash(e.codigo)]->next);

        nuevo->next = r->tabla[hash(e.codigo)]->next->next;
        r->tabla[hash(e.codigo)]->next = nuevo;
        *exito = 1;
        *cant++;
    }
}

#endif // REBALSE_SEPARADO_H