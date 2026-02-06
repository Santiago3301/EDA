#include <stdio.h>
#include <malloc.h>

typedef struct n{
  int valor;
  struct n* sig;
}Nodo;

Nodo* crear_nodo(int x);
