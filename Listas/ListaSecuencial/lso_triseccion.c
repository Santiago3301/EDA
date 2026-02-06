#include <stdio.h>
#include <stdlib.h>

#include "../../utils.h"

#define MAX 10

typedef struct{
    int V[MAX];
    int ult;
}LSO;

void initLSO(LSO *lista);
void localizarLSO(LSO lista, int x, int *pos, int *exito);
void altaLSO(LSO *lista, int x, int *exito);
void bajaLSO(LSO *lista, int x, int *exito);
void mostrarLSO(LSO lista);

int menuLSO(int system_clear_option){
    LSO lista;
    int x = 1;
    int exito;
    int opc = 1;

    initLSO(&lista);

    while(opc != 0){
        clear(system_clear_option);
        printf("Lista Secuencial Ordenada! (busqueda por triseccion)\nTipo: Numeros Enteros\nMAX = %d\n", MAX);
        mostrarLSO(lista);
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
                altaLSO(&lista, x, &exito);
                pause();
                break;
            case 2:
                printf("\nIngrese elemento a eliminar: ");
                scanf("%d", &x);
                bajaLSO(&lista, x, &exito);
                pause();
                break;
            case 0: break;
            default: break;
        }

    }

    printf("Gracias por usar. Vuelva prontos!\n");

    return 0;
}

void initLSO(LSO *lista){
    lista->ult = -1;
    for(int i=0; i<MAX ; i++){
        lista->V[i] = -999;
    }
}

void localizarLSO(LSO lista, int x, int *pos, int *exito){
    int li = 0;
    int ls = lista.ult; 
    int m = (li + ls)/2;
    while(li <= ls && lista.V[m] != x){
        if(lista.V[m] < x) li = m+1;
        else ls = m-1;
        m = (li + ls)/2;
    }
    *exito = (li <= ls);
    if(*exito == 1) *pos = m;
    else *pos = li;
}

void altaLSO(LSO *lista, int x, int *exito){
    int pos;
    *exito = 0;
    localizarLSO(*lista, x, &pos, exito);
    if(*exito == 1){
        printf("Ya esta el %d en la lista. Matate y grabalo.\n", x);
        pause();
    }else if(lista->ult < MAX-1){
        for(int i = lista->ult + 1; i>pos; i--){
            lista->V[i] = lista->V[i-1];
        }
        lista->V[pos] = x;
        lista->ult += 1;
        printf("Se inserto el %d B)\n", x);
        *exito = 1;
    }else printf("No hay espacio :'v");
}

void bajaLSO(LSO *lista, int x, int *exito){
    int pos;
    *exito = 0;
    localizarLSO(*lista, x, &pos, exito);
    if(*exito == 0){
        printf("No se encontro %d en la lista. Matate y grabalo", x);
    }else{
        int i = pos;
        while(i < lista->ult){
            lista->V[i] = lista->V[i+1];
            i++;
        }
        lista->ult -= 1;
        printf("Elemento %d eliminado B)", x);
        *exito = 1;
    }
}

void mostrarLSO(LSO lista){
    printf("Lista: [ ");
    int i = 0;
    while(i < lista.ult){
        printf("%d | ", lista.V[i]);
        i++;
    }
    if(lista.ult > -1) printf("%d ", lista.V[lista.ult]);
    printf("]\n");
}
