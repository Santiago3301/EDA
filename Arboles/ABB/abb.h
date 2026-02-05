/*
NOTAS:

Esta implementacion de ABB es iteraiva.
Una implementacion recursiva quiza sea mas eficiente y breve,
pero no mas facil de entender jaj

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct n{
  int valor;
  struct n* izq;
  struct n* der;
}Nodo;

typedef struct{
  Nodo* raiz;
  Nodo* cursor;
  Nodo* anterior;
  int cant;
}ABB;

// GEMINI: Estructura auxiliar para la cola de nodos
typedef struct q {
    Nodo* dato;
    struct q* sig;
} Cola;

void encolar(Cola** frente, Cola** final, Nodo* n) {
    if (n == NULL) return;
    Cola* nuevo = (Cola*)malloc(sizeof(Cola));
    nuevo->dato = n;
    nuevo->sig = NULL;
    if (*frente == NULL) {
        *frente = *final = nuevo;
    } else {
        (*final)->sig = nuevo;
        *final = nuevo;
    }
}

Nodo* desencolar(Cola** frente, Cola** final) {
    if (*frente == NULL) return NULL;
    Cola* aux = *frente;
    Nodo* n = aux->dato;
    *frente = (*frente)->sig;
    if (*frente == NULL) *final = NULL;
    free(aux);
    return n;
}


void initABB(ABB* arbol){
  arbol->raiz = NULL;
  arbol->cursor = NULL;
  arbol->anterior = NULL;
  arbol->cant = 0;
}

void liberarABB(Nodo* n){
  if(n == NULL) return;
  liberarABB(n->izq);
  liberarABB(n->der);
  free(n);
}

void localizarABB(ABB *arbol, int x, int *exito){
  arbol->cursor = arbol->raiz;
  arbol->anterior = NULL;

  while(arbol->cursor != NULL && arbol->cursor->valor != x){
    arbol->anterior = arbol->cursor;
    if(x < arbol->cursor->valor){
      arbol->cursor = arbol->cursor->izq;
    } else{
      arbol->cursor = arbol->cursor->der;
    }
  }

  *exito = (arbol->cursor != NULL); //llegó a nodo externo -> fracasó

}

Nodo* crearNodo(int x){
  Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));

  if(nuevo == NULL) return NULL;

  nuevo->valor = x;
  nuevo->izq = NULL;
  nuevo->der = NULL;
  return nuevo;
}

void altaABB(ABB* arbol, int x, int *exito){
  localizarABB(arbol, x, exito);
  if(*exito == 1){
    *exito = 0; //elemento ya existe 
    printf("\nYa existe elemento %d\n", x); 
  }else{
    Nodo* nuevo = crearNodo(x);
    if(nuevo == NULL) *exito = -1; //falla de memoria

    //Caso 1: arbol vacio
    if(arbol->raiz == NULL){
      arbol->raiz = nuevo;
    }else{
      //Caso 2: arbol no vacio -> nuevo nodo es hijo de anterior
      //2a: hijo izquierdo
      if(x < arbol->anterior->valor){
        arbol->anterior->izq = nuevo;
      }else{
        //2b: hijo derecho
        arbol->anterior->der = nuevo;
      }
    }
    
    arbol->cant++;
    *exito = 1;
    printf("\nSe agrego %d al arbol\n", x);
  }

}

void bajaABB(ABB *arbol, int x, int *exito){
  localizarABB(arbol, x, exito);
  if(exito == 0){
    printf("\nNo se encontro %d\n", x);
  }else{
    //nodo es hijo derecho de otro
    int der = (arbol->anterior != NULL && arbol->anterior->der == arbol->cursor);
    //nodo es la raiz
    int raiz = (arbol->raiz == arbol->cursor);
    //Caso 1: nodo no tiene hijos
    if(arbol->cursor->izq == NULL && arbol->cursor->der == NULL){
      //nodo es la raiz
      if(raiz) arbol->raiz = NULL;
      else{
        if(der) arbol->anterior->der = NULL;
        else arbol->anterior->izq = NULL;
      }
    }
    //Caso 2: nodo tiene 1 hijo
    //2a: tiene hijo izq
    if(arbol->cursor->izq != NULL && arbol->cursor->der == NULL){
      //nodo es la raiz
      if(raiz){
        arbol->raiz = arbol->cursor->izq;
      }else{ //tiene padre
        if(der) arbol->anterior->der = arbol->cursor->izq;
        else arbol->anterior->izq = arbol->cursor->izq;
      }
    }
    //2b: tiene hijo der
    if(arbol->cursor->izq == NULL && arbol->cursor->der != NULL){
      //nodo es la raiz
      if(raiz){
        arbol->raiz = arbol->cursor->der;
      }else{
        if(der) arbol->anterior->der = arbol->cursor->der;
        else arbol->anterior->izq = arbol->cursor->der;
      }
    }
    //Caso 3: tiene 2 hijos
    if(arbol->cursor->izq != NULL && arbol->cursor->der != NULL){
      //tomo mayor de los menores
      Nodo* auxcur = arbol->cursor->izq;
      Nodo* auxcur_anterior = auxcur;
      while(auxcur->der != NULL){
        auxcur_anterior = auxcur;
        auxcur = auxcur->der;
      }

      if(auxcur != auxcur_anterior){
        auxcur_anterior->der = auxcur->izq;
        auxcur->izq = arbol->cursor->izq;
      }

      auxcur->der = arbol->cursor->der;

      if(raiz) arbol->raiz = auxcur;
      else{
        if(der) arbol->anterior->der = auxcur;
        else arbol->anterior->izq = auxcur;
      }

    }

    arbol->cant--;
    free(arbol->cursor);
    printf("\nElemento %d eliminado\n", x);
  }
}

void inOrden(Nodo* raiz){
  if(raiz == NULL) return;
  inOrden(raiz->izq);
  printf(" %d |", raiz->valor);
  inOrden(raiz->der);
}

//Codigo copiado o de IA
//ni en pedo me pongo a programar la impresion del arbol

void treeprint(Nodo *root, int level) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++)
        printf(i == level - 1 ? "|-" : "  ");
    printf("%d\n", root->valor);
    treeprint(root->izq, level + 1);
    treeprint(root->der, level + 1);
}

void barridoPorNiveles(ABB arbol) {
    if (arbol.raiz == NULL) {
        printf("Arbol vacio.\n");
        return;
    }

    Cola *frente = NULL, *final = NULL;
    encolar(&frente, &final, arbol.raiz);

    printf("Barrido por niveles: |");
    while (frente != NULL) {
        Nodo* actual = desencolar(&frente, &final);
        printf(" %d |", actual->valor);

        if (actual->izq != NULL) encolar(&frente, &final, actual->izq);
        if (actual->der != NULL) encolar(&frente, &final, actual->der);
    }
    printf("\n");
}