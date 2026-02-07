#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "Listas/menu_listas.c"
//#include "Listas/ListaVinculada/linkedlist.c"
//#include "Arboles/ABB/arbol_binario_busq"

int main(){
  int system_clear_option;
  int opc = 1;

  printf("Seleccione su tipo de Sistema Operativo\n");
  printf("1. Windows\n2. Linux\nOpcion: ");
  scanf("%d", &system_clear_option);

  while(opc != 0){
    clear(system_clear_option);
    printf("Implementacion de Estructuras de Datos!\n");
    printf("Santiago Velazquez - feb. 2026\n");
    printf("Ing. en Computación - UNSL\n\n");
    printf("Seleccine una categoria:\n");
    printf("1. Listas\n2. Arboles\n3. Rebalses\n0. Salir\nOpcion: ");
    scanf("%d", &opc);

    switch(opc){
      case 1:
          menuListas(system_clear_option);
          break;
      case 2:
          printf("\nud. selecciono arboles\n");
          pause();
          break;
      case 3:
          printf("\nud. selecciono rebalses\n");
          pause();
          break;
      case 0:
          break;
    }

  }

  printf("\nGracias por usar, vuelva prontos!\n");

  return 0;
}
