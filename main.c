#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "Listas/menu_listas.c"
//#include "Listas/ListaVinculada/linkedlist.c"
//#include "Arboles/ABB/arbol_binario_busq"

int main(){
  int system_clear_option;
  int opc = 1;
  int intros = 1;

  introduccion_estructuras(system_clear_option);
  clear(system_clear_option);

  printf("Seleccione su tipo de Sistema Operativo\n");
  printf("1. Windows\n2. Linux\nOpcion: ");
  scanf("%d", &system_clear_option);
  

  while(opc != 0){
    clear(system_clear_option);
    printf("Implementacion de Estructuras de Datos!\n");
    printf("Santiago Velazquez - feb. 2026\n");
    printf("Ing. en Computación - UNSL\n\n");
    printf("Seleccine una categoria:\n");
    printf("1. Listas\n2. Arboles\n3. Rebalses\n");
    if(intros == 1) printf("4. Desactivar textos introductorios\n");
    else printf("4. Activar textos introductorios\n");
    printf("0. Salir\nOpcion: ");
    scanf("%d", &opc);

    switch(opc){
      case 1:
          if(intros == 1){
            introduccion_listas(system_clear_option);
          }
          menuListas(system_clear_option);
          break;
      case 2:
          if(intros == 1){
            clear(system_clear_option);
            printf("intro a arboels");
          }
          printf("\nOpcion en proceso\n");
          pause();
          break;
      case 3:
          if(intros == 1){
            clear(system_clear_option);
            printf("intro a rebalses\n");
          }
          printf("\nOpcion en proceso\n");
          pause();
          break;
      case 4:
          if(intros == 1){
            intros = 0;
            printf("\nTextos introductorios desactivados.\n");
          }else{
            intros = 1;
            printf("\nTextos introductorios activados.\n");
          }
          pause();
      case 0:
          break;
    }

  }

  printf("\nGracias por usar, vuelva prontos!\n");

  return 0;
}
