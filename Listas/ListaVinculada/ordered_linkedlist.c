//no preguntes por que el nombre del archivo esta en ingles
//si el codigo esta en español
//no preguntes, solo gozalo.jpg

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct n{
  int valor;
  struct n* sig;
}Nodo;

typedef struct{
  Nodo* acc;
  Nodo* cur;
  Nodo* aux;
}Lista;

int isEmpty(Lista lista);
void init(Lista *lista);
void vaciar(Lista *lista);
void localizar(int x, Lista *lista, int *exito);
Nodo* crear_nodo(int val_nuevo);
void alta(int x, Lista *lista, int *exito);
void baja(int x, Lista *lista, int *exito);
void mostrar(Lista lista);

int main(){  
  int x = 1;
  Lista lista;
  init(&lista);
  int exito;
  int opc = 1;

  while(opc != 0){
    system("clear");
    printf("Lista Vinculada Ordenada!\n");
    printf("Tipo: Numeros Enteros\n");
    mostrar(lista);
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
            alta(x, &lista, &exito);
            getchar();
            getchar();
            break;
        case 2:
            printf("\nIngrese elemento a eliminar: ");
            scanf("%d", &x);
            baja(x, &lista, &exito);
            getchar();
            getchar();
            break;
        case 0: break;
        default: break;
    }

  }

  printf("Gracias por usar, vuelva prontos!\n");
  vaciar(&lista);

}

int isEmpty(Lista lista){
  return (lista.acc->sig == NULL);
}

void init(Lista *lista){
  lista->acc = lista->cur = lista->aux = NULL;
}

void reset(Lista *lista){
  lista->cur = lista->acc;
  lista->aux = lista->acc;
}

void vaciar(Lista *lista){
  reset(lista);
  while(lista->cur != NULL){
    lista->acc = lista->cur->sig;
    free(lista->cur);
    lista->cur = lista->acc;
  }
}

void mostrar(Lista lista){
  reset(&lista);
  printf("Lista: o--> ");
  while(lista.cur != NULL){
    printf("[%d|o]--> ", lista.cur->valor);
    lista.cur = lista.cur->sig;
  }
  printf("|Ii\n");
}

void localizar(int x, Lista *lista, int *exito){
  reset(lista);
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

Nodo* crear_nodo(int val_nuevo){
  Nodo* nuevo = malloc(sizeof(Nodo));
  nuevo->valor = val_nuevo;
  nuevo->sig = NULL;
  return nuevo;
}

void alta(int x, Lista *lista, int *exito){
  localizar(x, lista, exito);
  if(*exito == 1){
    printf("\nNo se pudo añadir el elemento :'v\n");
  }else {
    Nodo* nuevo = crear_nodo(x);
    if(lista->acc == lista->cur){
      nuevo->sig = lista->acc;
      lista->acc = nuevo;
    }else{
      nuevo->sig = lista->cur;
      lista->aux->sig = nuevo;
    }
    printf("\nElemento agregado ;v\n");
  }
}

void baja(int x, Lista *lista, int *exito){
  localizar(x, lista, exito);
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