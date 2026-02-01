#ifndef L2L_H
#define L2L_H

#include <stdio.h>
#include "LSO.h"

#define MAX_DESCRIPTORES 10

typedef struct {
    int xd; //Clave de acceso: valor x de la primera nupla de la sublista
    LSO sublista;
} Descriptor;

typedef struct {
    Descriptor ListaDescriptores[10];
    int ult;
} L2L;

void init_L2L(L2L *lista){
    lista->ult = -1;
}

void liberar_L2L(L2L *lista){
    for(int i = 0; i <= lista->ult; i++){
        liberar_LSO(&lista->ListaDescriptores[i].sublista);
    }
    lista->ult = -1;
}

void localizar_Descriptor(L2L lista, int x, int *pos, int *exito){
    *exito = 0;
    if(lista.ult == -1){
        printf("estructura vacia\n");
        *pos = 0;
        return;
    }

    int li = 0;
    int ls = lista.ult;
    
    while(li < ls){
        int m = (li + ls + 1)/2;
        if(x < lista.ListaDescriptores[m].xd) ls = m - 1;
        else li = m;
    }
    *pos = li;
    printf("candidato: descriptor en pos %d\n", *pos);
    *exito = 1;
}

void localizar_L2L(L2L lista, int x, int *posDesc, int *posSublista, int *exito){
    localizar_Descriptor(lista, x, posDesc, exito);
    
    //Caso 1: se halló un descriptor -> búsqueda en la sublista correspondiente
    localizar_LSO(lista.ListaDescriptores[*posDesc].sublista, x, posSublista, exito);

    if(*posDesc > lista.ult){
    *exito = 0;
    *posSublista = -1;
    return;
    }

    if(*exito == 0){
        //Caso 1a: no se halló en la sublista
        *posSublista = -1;
        return;
    }
    //Caso 1b: se halló en la sublista -> posSublista ya está seteado
    *exito = 1;
}

void alta_L2L(L2L *lista, Nupla X, int *exito){
    //Caso 1: lista de descriptores vacía
    if(lista->ult == -1){
        printf("estructura vacia -> creando primer descriptor\n");
        lista->ult = 0;
        lista->ListaDescriptores[0].xd = X.x;
        init_LSO(&lista->ListaDescriptores[0].sublista);
        alta_LSO(&lista->ListaDescriptores[0].sublista, X, exito);
        return;
    }

    int posDesc = 0;
    int posSublista = 0;
    int exitoLocal = 0;

    localizar_L2L(*lista, X.x, &posDesc, &posSublista, exito);

    //Caso 2: x ya existe en la lista
    if(*exito == 1){
        *exito = 0;
        return;
    }
    //Caso 3: no se halló x
    //Caso 3a: se halló sublista adecuada
    alta_LSO(&lista->ListaDescriptores[posDesc].sublista, X, &exitoLocal);
    if(exitoLocal == 1){
        if(X.x < lista->ListaDescriptores[posDesc].xd){
            lista->ListaDescriptores[posDesc].xd = X.x;
        }
        *exito = 1;
        return; //Inserción exitosa
    }else if(exitoLocal == -1){
        printf("sublista llena: desdoblamiento necesario\n");
        if(lista->ult == MAX_DESCRIPTORES - 1){
            printf("ERROR: lista de descriptores llena\n");
            *exito = -1;
            return;
        }
        //Caso 3b: sublista llena
        Descriptor nuevoDesc;
        nuevoDesc.sublista.ult = -1;
        init_LSO(&nuevoDesc.sublista);
        //int m = MAX_SUBLISTA;
        int m = lista->ListaDescriptores[posDesc].sublista.ult + 1;

        //arreglo auxiliar para ordenar las nuplas
        Nupla aux[m + 1];
        int iOrig = 0, iAux = 0;

        while (iOrig < m && lista->ListaDescriptores[posDesc].sublista.lista[iOrig].x < X.x) {
            aux[iAux] = lista->ListaDescriptores[posDesc].sublista.lista[iOrig];
            iAux++;
            iOrig++;
        }
        aux[iAux] = X;
        iAux++;
        while(iOrig < m){
            aux[iAux] = lista->ListaDescriptores[posDesc].sublista.lista[iOrig];
            iAux++;
            iOrig++;
        }

        //punto de corte
        int k = m/2 + 1;
        lista->ListaDescriptores[posDesc].sublista.ult = k - 1;

        for(int i = 0; i < k; i++){
            lista->ListaDescriptores[posDesc].sublista.lista[i] = aux[i];
        }

        for(int i = k; i < m + 1; i++){
            nuevoDesc.sublista.lista[i - k] = aux[i];
            nuevoDesc.sublista.ult++;
        }

        //actualizacion de descriptores
        lista->ListaDescriptores[posDesc].xd = lista->ListaDescriptores[posDesc].sublista.lista[0].x;
        nuevoDesc.xd = nuevoDesc.sublista.lista[0].x;

        //corrimientos de descriptores -> insertar nuevo descriptor
        for(int i = (lista->ult)+1; i>posDesc+1; i--){
            lista->ListaDescriptores[i] = lista->ListaDescriptores[i-1];
        }
        lista->ListaDescriptores[posDesc+1] = nuevoDesc;
        lista->ult += 1;

        *exito = 1;
    }
    
}

void mostrarDescriptores(L2L lista){
    printf("[| ");
    for(int i=0; i < lista.ult+1; i++){
         printf("%d ", i);
         if(lista.ListaDescriptores[i].xd >= 10){
           printf(" | ");
         }else printf("| ");
    }
    printf("|]\n");
    printf("[| ");
    for(int i=0; i < lista.ult+1; i++){
         printf("%d | ", lista.ListaDescriptores[i].xd);
    }
    printf("]");
}

#endif // L2L_H
