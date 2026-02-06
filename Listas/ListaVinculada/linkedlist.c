#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "../../utils.h"
#include "nodo.h"

typedef struct{
  Nodo* acc;
  Nodo* cur;
  Nodo* aux;
}LVD;

void initLVD(LVD* lista);
void resetLVD(LVD* lista);
void vaciarLVD(LVD *lista);
void localizarLVD(int x, LVD *lista, int *exito);
void altaLVD(int x, LVD *lista, int *exito);
void bajaLVD(int x, LVD *lista, int *exito);
void mostrarLVD(LVD lista);

int menuLVD(int system_clear_option){  
  int x = 1;
  LVD lista;
  initLVD(&lista);
  int exito;
  int opc = 1;

  while(opc != 0){
    clear(system_clear_option);
    printf("Lista Vinculada!\n");
    printf("Tipo: Numeros Enteros\n");
    mostrarLVD(lista);
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
            altaLVD(x, &lista, &exito);
            pause();
            break;
        case 2:
            printf("\nIngrese elemento a eliminar: ");
            scanf("%d", &x);
            bajaLVD(x, &lista, &exito);
            pause();
            break;
        case 0: break;
        default: break;
    }

  }

  //printf("Gracias por usar, vuelva prontos!\n");
  vaciarLVD(&lista);

}

void initLVD(LVD *lista){
  lista->acc = lista->aux = lista->cur = NULL;
}

int isEmptyLVD(LVD lista){
  return (lista.acc->sig == NULL);
}

void resetLVD(LVD *lista){
  lista->cur = lista->acc;
  lista->aux = lista->acc;
}

void vaciarLVD(LVD *lista){
  resetLVD(lista);
  while(lista->cur != NULL){
    lista->acc = lista->cur->sig;
    free(lista->cur);
    lista->cur = lista->acc; 
  }
}

void mostrarLVD(LVD lista){
  resetLVD(&lista);
  printf("Lista: o--> ");
  while(lista.cur != NULL){
    printf("[%d|o]--> ", lista.cur->valor);
    lista.cur = lista.cur->sig;
  }
  printf("|Ii\n");
}

void localizarLVD(int x, LVD *lista, int *exito){
  resetLVD(lista);
  while(lista->cur != NULL && lista->cur->valor != x){
    lista->aux = lista->cur;
    lista->cur = lista->cur->sig;
  }
  
  if(lista->cur != NULL && lista->cur->valor == x){
    *exito = 1;
  }else{
    *exito = 0;
  }
}

void altaLVD(int x, LVD *lista, int *exito){
  localizarLVD(x, lista, exito);
  if(*exito == 1){
    printf("\nElemento %d ya existe en la lista. Matate y grabalo.\n", x);
  }else{
    Nodo* nuevo = crear_nodo(x);
    nuevo->sig = lista->acc;
    lista->acc = nuevo;
    printf("\nElemento agregado ;v\n");
  }
}

void bajaLVD(int x, LVD *lista, int *exito){
  localizarLVD(x, lista, exito);
  if(*exito == 1){
    //caso 1: primer elemento
    if(lista->acc == lista->cur){
      lista->acc = lista->cur->sig;
    }else{
      //caso 2: elemento intermedio
    lista->aux->sig = lista->cur->sig;

    }
    free(lista->cur);
    printf("\nSe elimino el elemento %d ;v\n", x);
  }else{
    printf("\nNo se encontro %d en la estrucutura. Matate y grabalo\n", x);
    *exito = 0;
  }
}
