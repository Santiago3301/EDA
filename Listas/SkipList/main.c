#include <stdio.h>
#include "skiplist.h"
#include <time.h>

typedef struct{
  int x;
  int y;
}nupla;

int main(){
  srand(time(NULL));
  int N = 9;
  nupla X[N];
  int input, exito;
  SKIPLIST sl;
  init_skiplist(&sl);

  for(int i=0; i<N; i++){
    printf("ingrese X[%d]: ", i);
    scanf("%d", &input);
    X[i].x = input;
    X[i].y = i+1;
    alta_skiplist(&sl, X[i].x, X[i].y, &exito);
    printf("\n");
    mostrar_skiplist(sl);
    printf("\n");
  }
  return 0;
}
