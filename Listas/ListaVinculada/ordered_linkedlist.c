//no preguntes por que el nombre del archivo esta en ingles
//si el codigo esta en español
//no preguntes, solo gozalo.jpg

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "../../utils.h"
#include "nodo.h"

typedef struct{
  Nodo* acc;
  Nodo* cur;
  Nodo* aux;
}LVO;

int isEmptyLVO(LVO lista);
void initLVO(LVO *lista);
void vaciarLVO(LVO *lista);
void localizarLVO(int x, LVO *lista, int *exito);
void altaLVO(int x, LVO *lista, int *exito);
void bajaLVO(int x, LVO *lista, int *exito);
void mostrarLVO(LVO lista);

int menuLVO(int system_clear_option){  
  int x = 1;
  LVO lista;
  initLVO(&lista);
  int exito;
  int opc = 1;

  while(opc != 0){
    clear(system_clear_option);
    printf("Lista Vinculada Ordenada!\n");
    printf("Tipo: Numeros Enteros\n");
    mostrarLVO(lista);
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
            altaLVO(x, &lista, &exito);
            pause();
            break;
        case 2:
            printf("\nIngrese elemento a eliminar: ");
            scanf("%d", &x);
            bajaLVO(x, &lista, &exito);
            pause();
            break;
        case 0: break;
        default: break;
    }

  }

  //printf("Gracias por usar, vuelva prontos!\n");
  vaciarLVO(&lista);

}

int isEmptyLVO(LVO lista){
  return (lista.acc->sig == NULL);
}

void initLVO(LVO *lista){
  lista->acc = lista->cur = lista->aux = NULL;
}

void resetLVO(LVO *lista){
  lista->cur = lista->acc;
  lista->aux = lista->acc;
}

void vaciarLVO(LVO *lista){
  resetLVO(lista);
  while(lista->cur != NULL){
    lista->acc = lista->cur->sig;
    free(lista->cur);
    lista->cur = lista->acc;
  }
}

void mostrarLVO(LVO lista){
  resetLVO(&lista);
  printf("Lista: o--> ");
  while(lista.cur != NULL){
    printf("[%d|o]--> ", lista.cur->valor);
    lista.cur = lista.cur->sig;
  }
  printf("|Ii\n");
}

void localizarLVO(int x, LVO *lista, int *exito){
  resetLVO(lista);
  while(lista->cur != NULL && lista->cur->valor < x){
    lista->aux = lista->cur;
    lista->cur = lista->cur->sig;
  }
  
  if(lista->cur != NULL && lista->cur->valor == x){
    *exito = 1;
  }else{
    *exito = 0;
  }
}

void altaLVO(int x, LVO *lista, int *exito){
  localizarLVO(x, lista, exito);
  if(*exito == 1){
    printf("\nEl elemento %d ya se encuentra en la lista\n", x);
  }else {
    Nodo* nuevo = crear_nodo(x);
    if(nuevo == NULL){
      printf("\nMemoria insuficiente\n");
      *exito = -1;
      return;
    }
    //Caso 1: x es menor al primer elemento 
    if(lista->acc == lista->cur){
      nuevo->sig = lista->acc;
      lista->acc = nuevo;
    }else{
      //Caso 2: insertar en posicion intermedia
      nuevo->sig = lista->cur;
      lista->aux->sig = nuevo;
    }
    printf("\nElemento agregado ;v\n");
    *exito = 1;
  }
}

void bajaLVO(int x, LVO *lista, int *exito){
  localizarLVO(x, lista, exito);
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
    printf("\nNo se encontro %d en la estructura. Matate y grabalo\n", x);
    *exito = 0;
  }
}
