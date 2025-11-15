#include <stdio.h>
#include "skiplist.h"

typedef struct{
  int x;
  int y;
}nupla;

int main(){
  int N = 10;
  int arr[] = {5,2,7,1,6,3,8,4,9,10};
  N = sizeof(arr)/sizeof(int);
  nupla X[N];
  for(int i=0; i<N; i++){
    X[i].x = arr[i];
    X[i].y = i+1;
  }

  SKIPLIST sl;
  init_skiplist(&sl);

  int exito;
  for(int i=0; i<N; i++){
    printf("%d: %d\n",i, X[i].y);
    alta_skiplist(&sl, X[i].x, X[i].y, &exito);
  }
  printf("\n\n");
  mostrar_skiplist(sl);

  return 0;
}
