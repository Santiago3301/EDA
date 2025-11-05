#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct n{
  float valor;
  struct n* izq;
  struct n* der;
}Nodo;

typedef struct{
  Nodo* raiz;
  Nodo* cursor;
  Nodo* aux;
  int cant;
}ABB;

void initABB(ABB* arbol){
  arbol->raiz = NULL;
  arbol->cursor = NULL;
  arbol->aux = NULL;
  arbol->cant = 0;
}

int localizarABB(ABB* arbol, float x, int* costo){
  if(arbol->cursor == NULL) return 0;
  (*costo)++;
  //printf("costo: %d\n", *costo);
  if(arbol->cursor->valor == x) return 1; //encontrado
  arbol->aux = arbol->cursor;
  if(arbol->cursor->valor < x){
    arbol->cursor = arbol->cursor->der;
  }else arbol->cursor = arbol->cursor->izq;
  
  return localizarABB(arbol,x,costo);
}

Nodo* crearNodo(float x){
  Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
  if(nuevo == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  nuevo->valor = x;
  nuevo->izq = NULL;
  nuevo->der = NULL;
  return nuevo;
}

int altaABB(ABB* arbol, float x){
  int costo = 0;
  arbol->cursor = arbol->raiz;
  arbol->aux = NULL;
  int exito = localizarABB(arbol,x,&costo);
  if(exito == 1) return 0; //ya está  

  Nodo* nuevo = crearNodo(x);
  if(arbol->raiz == NULL){
    arbol->raiz = nuevo;
  }else if(x > arbol->aux->valor) arbol->aux->der = nuevo;
  else arbol->aux->izq = nuevo;
  arbol->cant++;
  return 1;
}

void inOrden(Nodo* raiz){
  if(raiz == NULL) return;
  inOrden(raiz->izq);
  printf("%.0f ", raiz->valor);
  inOrden(raiz->der);
}



void treeprint(Nodo *root, int level) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++)
        printf(i == level - 1 ? "|-" : "  ");
    printf("%.0f\n", root->valor);
    treeprint(root->izq, level + 1);
    treeprint(root->der, level + 1);
}
