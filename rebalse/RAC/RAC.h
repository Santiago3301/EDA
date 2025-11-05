#ifndef RAC_H_
#define RAC_H_

#define MRAC 7 

#define virgen '*'
#define libre '-'
#define ocupada 'o'

typedef struct{
  char estado;
  int x;
}celda;

typedef struct{
  celda tabla[MRAC];
  int ult;
}RAC;

int hash(int x){
    return (x % MRAC);
}

void init_RAC(RAC *rebalse_cuadratico){
  rebalse_cuadratico->ult = -1;
  for(int i=0; i<MRAC; i++){
    rebalse_cuadratico->tabla[i].estado = virgen; 
  }
}

int localizar_RAC(RAC rebalse_cuadratico, int x){
  int index = hash(x);
  int k = 1;
  int cont = 0; //consultas
  while(rebalse_cuadratico.tabla[index].x != x && cont < MRAC){
    if(rebalse_cuadratico.tabla[index].estado == virgen) {
      printf("celda: %d -> estado: virgen\n", index);
      return index;
    }
    printf("celda: %d -> estado: ", index);
    if(rebalse_cuadratico.tabla[index].estado == ocupada) printf("ocupada\n");
    else if (rebalse_cuadratico.tabla[index].estado == libre) printf("libre\n");
    index = (index+k) % MRAC;
    cont++;
    k++;
  }
  printf("se consultaron %d celdas. Celda %d -> estado: ", cont, index);
  if(rebalse_cuadratico.tabla[index].estado == ocupada) printf("ocupada\n");
  else if(rebalse_cuadratico.tabla[index].estado == libre) printf("libre\n");
  else printf("virgen\n");
  return index;
}

int alta_RAC(RAC *rebalse_cuadratico, int x){
  if(rebalse_cuadratico->ult == MRAC-1) return -1; //estructura llena
  int index = localizar_RAC(*rebalse_cuadratico, x);
  if(rebalse_cuadratico->tabla[index].estado == ocupada && rebalse_cuadratico->tabla[index].x == x){
    return -1;
    //alta fracasa
  }
  if(rebalse_cuadratico->tabla[index].estado == virgen || rebalse_cuadratico->tabla[index].estado == libre){
    rebalse_cuadratico->tabla[index].x = x;
    rebalse_cuadratico->tabla[index].estado = ocupada;
    rebalse_cuadratico->ult++;
    return 1; //alta exitosa
  }
  return -1;  
}

//   ---- Cambiar implementacion para RAC ----

int baja_RAC(RAC *rebalse_cuadratico, int x){
  if(rebalse_cuadratico->ult == -1) return -1; //estructura vacia
  int index = localizar_RAC(*rebalse_cuadratico, x);
  if(index < 0) return 0; //no encontrado
  rebalse_cuadratico->tabla[index].estado = libre;
  rebalse_cuadratico->ult--;
  return 1; //baja exitosa
}

int evocacion_RAC(RAC rebalse_cuadratico, int x){ //como las nuplas son solo x -> evocar = pertenencia
  int index = localizar_RAC(rebalse_cuadratico, x);
  if(index > -1) return rebalse_cuadratico.tabla[index].x; //encontrado -> retorna x
  return -1; //no esta (la estructura no almacena negativos)
}

void mostrar_RAC(RAC rebalse_cuadratico){
  printf("Mostrando Rebalse Abierto Cuadratico:\n");
  printf("[ ");
  for(int i=0; i<MRAC; i++){
    printf("%d", i);
    if(i < MRAC-1) printf(" | ");
  }
  printf(" ]\n");

  printf("[ ");
  for(int i=0; i<MRAC; i++){
    if(rebalse_cuadratico.tabla[i].estado == ocupada) printf("%d", rebalse_cuadratico.tabla[i].x);
    else printf("%c", rebalse_cuadratico.tabla[i].estado);
    if(i < MRAC-1) printf(" | ");
  }
  printf(" ]");
}

#endif //RAL_H_
