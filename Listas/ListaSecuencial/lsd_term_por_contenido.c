#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"

#define MAX 10
#define FIN -999

typedef struct{
    int V[MAX+1];
}LSC; //Lista Secuencial (desordenada con terminacion dada por) Contenido

void initLSC(LSC *lista);
void localizarLSC(LSC lista, int x, int *pos, int *exito);
void altaLSC(LSC *lista, int x, int *exito);
void bajaLSC(LSC *lista, int x, int *exito);
void mostrarLSC(LSC lista);

int menuLSC(int system_clear_option){
    LSC lista;
    int opc = 1;
    int exito;
    int x = 0;

    initLSC(&lista);

    while(opc != 0){
        clear(system_clear_option);
        printf("Lista Secuencial con terminacion dada por contenido\nMAX = %d\n", MAX);
        printf("Tipo: Enteros positivos U {0}\n");
        mostrarLSC(lista);
        printf("Seleccione una opcion:\n");
        printf("1. Insertar un elemento\n");
        printf("2. Eliminar un elemento\n");
        printf("0. Salir\n");
        printf("\nOpcion: ");
        scanf("%d", &opc);
    
        switch(opc){
            case 1:
                printf("\nIngrese elemento a insertar: ");
                scanf("%d", &x);
                altaLSC(&lista, x, &exito);
                pause();
                break;
            case 2:
                printf("\nIngrese elemento a eliminar: ");
                scanf("%d", &x);
                bajaLSC(&lista, x, &exito);
                pause();
                break;
            case 0: break;
            default: break;
        }

    }
    //printf("\nGracias por usar. Vuelva prontos!\n");

    return 0;
}

void initLSC(LSC *lista){
    lista->V[0] = FIN;
}

void localizarLSC(LSC lista, int x, int *pos, int *exito){
    int i = 0;
    while(lista.V[i] != FIN && lista.V[i] != x){
        i++;
    }
    *pos = i;
    *exito = (lista.V[i] != FIN);
}

void altaLSC(LSC *lista, int x, int *exito){
    int pos;
    *exito = 0;
    localizarLSC(*lista, x, &pos, exito);
    if(*exito == 1){
        printf("Ya esta el %d en la lista. Matate y grabalo.\n", x);
    }else if(pos < MAX-1){
        lista->V[pos] = x;
        lista->V[pos+1] = FIN;
        printf("Se inserto el %d B)\n", x);
        *exito = 1;
    }else printf("No hay espacio :'v\n");
}

void bajaLSC(LSC *lista, int x, int *exito){
    int pos;
    *exito = 0;
    localizarLSC(*lista, x, &pos, exito);
    if(*exito == 0){
        printf("No se encontro %d en la lista. Matate y grabalo\n", x);
    }else{
        int i = pos;
        while(lista->V[i-1] != FIN){
            lista->V[i] = lista->V[i+1];
            i++;
        }
        printf("Elemento %d eliminado B)\n", x);
        *exito = 1;
    }
}

void mostrarLSC(LSC lista){
    printf("Lista: [ ");
    int i = 0;
    while(lista.V[i] != FIN){
        printf("%d | ", lista.V[i]);
        i++;
    }
    printf("* ");
    printf("]\n");
}
