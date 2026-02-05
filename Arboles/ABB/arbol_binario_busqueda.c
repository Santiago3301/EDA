#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

void clear(int x){
    if(x == 1) system("cls");
    else system("clear");
}

int main(){
    ABB arbol;
    initABB(&arbol);
    int opc = 1;
    int x;
    int exito;

    int system_clear_option = 2; 

    while(opc != 0){
        clear(system_clear_option);

        printf("Arbol Binario de Busqueda!\n");
        printf("Tipo: Enteros\n");
        printf("Arbol: \n");
        barridoPorNiveles(arbol);
        printf("\n1. Insertar un elemento\n");
        printf("2. Eliminar un elemento\n");
        printf("3. Mostrar arbol (Treeprint)\n");
        printf("0. Salir\n");
        printf("Opcion: ");

        scanf("%d", &opc);

        switch(opc){
            case 1:
                printf("\nIngrese el elemento a insertar: ");
                scanf("%d", &x);
                altaABB(&arbol, x, &exito);
                getchar();
                getchar();
                break;

            case 2:
                printf("\nIngrese el elemento a eliminar: ");
                scanf("%d", &x);
                bajaABB(&arbol, x, &exito);
                getchar();
                getchar();
                break;

            case 3:
                treeprint(arbol.raiz, 0);
                getchar();
                getchar();
            case 0:
                break;
        }

    }
    
    liberarABB(arbol.raiz);
    printf("Gracias por usar, vuelva prontos!\n");


}