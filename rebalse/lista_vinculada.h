#ifndef LISTA_VINCULADA_H
#define LISTA_VINCULADA_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "estudiante.h"

typedef struct n{
    Estudiante e;
    struct n* next;
}nodo;

typedef struct{
    nodo *acc;
    nodo *cur;
    nodo *aux;
}lista_vinculada;

void init_lista_vinculada(lista_vinculada *l){
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}

void reset_lista_vinculada(lista_vinculada *l){
    l->cur = l->acc;
    l->aux = l->acc;
}

int isEmpty_lista_vinculada(lista_vinculada l){
    return (l.acc == NULL);
}

int isOos_lista_vinculada(lista_vinculada l){ //Out of structure
    return (l.cur == NULL);
}

void forward_lista_vinculada(lista_vinculada *l){
    //si cur != aux, entonces aux->next = cur
    //entonces si hago forward(cur), tengo q hacer forward(aux)
    if(l->cur != l->aux) l->aux = l->aux->next;
    //si son iguales, dejo aux como estaba para tener el anterior referenciado
    l->cur = l->cur->next;
}

void localizar_lista_vinculada(lista_vinculada *l, char code[], int *exito){
    if(isEmpty_lista_vinculada(*l)){ //lista vacia
        //printf("lista vacia\n");
        *exito = -1;
        return;
    }
    reset_lista_vinculada(l);
    
    while(!isOos_lista_vinculada(*l) && strcmp(l->cur->e.codigo, code) != 0){
        //printf("lista->cur = %p\n", l->cur);
        //printf("forward\n");
        forward_lista_vinculada(l);
    }
    if(isOos_lista_vinculada(*l)) *exito = 0;
    else *exito = 1;
}

void alta_lista_vinculada(lista_vinculada *l, Estudiante e, int *exito){
    //printf("buscando\n");
    localizar_lista_vinculada(l, e.codigo, exito);
    if(*exito == 1){
        //printf("repetido\n");
        *exito = 0;
        return; //x ya esta en la lista
    }
    nodo *nuevo;
    nuevo = (nodo *)malloc(sizeof(nodo));
    if(nuevo == NULL){
        //printf("falla de asignacion de memoria\n");
        *exito = -1; //falla de asignacion de memoria
        return;
    }
    nuevo->e = e;
    if(*exito == -1){ //lista vacia
        nuevo->next = l->acc; //nuevo->next = NULL
        l->acc = l->aux = l->cur = nuevo;
    }else{
        l->aux->next = nuevo;
        nuevo->next = l->cur; //nuevo->next = null
        l->cur = nuevo;
    }
    *exito = 1;
    //printf("cargado\n");
}

void baja_lista_vinculada(lista_vinculada *l, char code[], int *exito){
    localizar_lista_vinculada(l, code, exito);
    if(*exito == -1 || *exito == 0) return; //lista vacia o no encontrado
    if(l->acc == l->cur){
        l->acc = l->aux = l->cur->next;
        free(l->cur);
        l->cur = l->acc;
    }else{
        l->aux->next = l->cur->next;
        free(l->cur);
        l->cur = l->aux->next;
    }
    *exito = 1;
}

void copy_lista_vinculada(lista_vinculada l, Estudiante *e){
    *e = l.cur->e;
}

#endif // LISTA_VINCULADA_H