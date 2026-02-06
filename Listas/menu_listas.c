#include <stdio.h>
#include <stdlib.h>

#include "../utils.h"
#include "ListaSecuencial/lsd_largo_conocido.c"
#include "ListaSecuencial/lsd_term_por_contenido.c"
#include "ListaSecuencial/lso_triseccion.c"
#include "ListaVinculada/linkedlist.c"
#include "ListaVinculada/ordered_linkedlist.c"
#include "ListaVinculada/nodo.c"

//#include "2LevelList/usoL2L.c"
#include "SkipList/skiplist.c"

//CAMBIAR A menuListas
void menuListas(int system_clear_option){
  int opc = 1;
  system_clear_option = 2;

  while(opc != 0){
    clear(system_clear_option);
    printf("---- > Listas < ----\n");

    printf("\nSeleccione una lista\n");
    printf("\n-- Listas Secuenciales: \n\n");
    printf("1. Lista Secuencial Desordenada (LSD)\n");
    printf("2. LSD con terminacion dada por contenido (LSC)\n");
    printf("3. Lista Secuencial Ordenada (LSO)\n\n");

    printf("\n-- Listas Vinculadas:\n\n");
    printf("4. Lista Vinculada Desordenada (LVD)\n");
    printf("5. Lista Vinculada Ordenada (LVO)\n\n");

    printf("\n-- Listas Avanzadas: \n\n");
    printf("6. SkipList (SL)\n7. Lista de 2 niveles (L2L)\n\n");
    
    printf("\n0. Volver al menu anterior\n");

    printf("\nOpcion: ");
    scanf("%d", &opc);

    switch (opc) {
      case 1:
        menuLSD(system_clear_option);
        break;
      
      case 2:
        menuLSC(system_clear_option);
        break;

      case 3:
        menuLSO(system_clear_option);
        break;
      
      case 4:
        menuLVD(system_clear_option);
        break;

      case 5:
        menuLVO(system_clear_option);
        break;
      
      case 6:
        testSkipList();
        break;

      case 0:
        break;
      default:
        printf("aun en desarrollo\n");
        pause(); 
    }

  }
}
