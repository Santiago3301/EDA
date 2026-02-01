#ifndef RAL_H_
#define RAL_H_

#define MRAL 7

#define virgen '*'
#define libre '-'
#define ocupada 'o'

typedef struct{
  char estado;
  int x;
}celda;

typedef struct{
  celda tabla[MRAL];
  int ult;
}RAL;

int hash(int x){
    return (x % MRAL);
}

void init_RAL(RAL *rebalse_lineal){
  rebalse_lineal->ult = -1;
  for(int i=0; i<MRAL; i++){
    rebalse_lineal->tabla[i].estado = virgen; 
  }
}

int localizar_RAL(RAL rebalse_lineal, int x){
  int index = hash(x);
  printf("hash = %d\n", index);
  int cont = 0; //consultas
  while(rebalse_lineal.tabla[index].x != x && cont < rebalse_lineal.ult){
    printf("index = %d\n", index);
    if(rebalse_lineal.tabla[index].estado == virgen) return index;
    index = (index+1) % MRAL;
    cont++;
  }
  return index;
}

int alta_RAL(RAL *rebalse_lineal, int x){
  if(rebalse_lineal->ult == MRAL-1) return -1; //estructura llena
  int index = localizar_RAL(*rebalse_lineal, x);
  if(rebalse_lineal->tabla[index].estado == ocupada) {printf("no hay celdas disponibles\n"); return 0;}
  printf("index = %d\n", index);   
  rebalse_lineal->tabla[index].x = x;
  rebalse_lineal->tabla[index].estado = ocupada;
  rebalse_lineal->ult++;
  printf("alta -> x = %d , estado: %c , ult: %d\n", rebalse_lineal->tabla[index].x, rebalse_lineal->tabla[index].estado, rebalse_lineal->ult);
  return 1; //alta exitosa
}

int baja_RAL(RAL *rebalse_lineal, int x){
  if(rebalse_lineal->ult == -1) return -1; //estructura vacia
  int index = localizar_RAL(*rebalse_lineal, x);
  if(index < 0) return 0; //no encontrado
  rebalse_lineal->tabla[index].estado = libre;
  rebalse_lineal->ult--;
  return 1; //baja exitosa
}

int evocacion_RAL(RAL rebalse_lineal, int x){ //como las nuplas son solo x -> evocar = pertenencia
  int index = localizar_RAL(rebalse_lineal, x);
  if(index > -1) return rebalse_lineal.tabla[index].x; //encontrado -> retorna x
  return -1; //no esta (la estructura no almacena negativos)
}

void mostrar_RAL(RAL rebalse_lineal){
  printf("Mostrando Rebalse Abierto Lineal:\n");
  printf("[ ");
  for(int i=0; i<MRAL; i++){
    printf("%d", i);
    if(i < MRAL-1) printf(" | ");
  }
  printf(" ]\n");

  printf("[ ");
  for(int i=0; i<MRAL; i++){
    if(rebalse_lineal.tabla[i].estado == ocupada) printf("%d", rebalse_lineal.tabla[i].x);
    else printf("%c", rebalse_lineal.tabla[i].estado);
    if(i < MRAL-1) printf(" | ");
  }
  printf(" ]\n");
}

#endif //RAL_H_
