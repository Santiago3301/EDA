#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void clear(int x){
    if(x == 1) system("cls");
    else system("clear");
}

int main(){

    Nodo* raiz = NULL;

    int opc = 1;
    int x;
    int exito = 0;

    int system_clear_option = 2; 

    while(opc != 0){
        clear(system_clear_option);

        printf("Arbol Binario Balanceado (AVL)!\n");
        printf("Tipo: Enteros\n");
        printf("Arbol: \n");
        barridoPorNiveles(raiz);
        printf("\n1. Insertar un elemento\n");
        printf("2. Eliminar un elemento\n");
        printf("3. Mostrar arbol (Treeprint)\n");
        printf("4. Mostrar arbol (print2D)\n");
        printf("0. Salir\n");
        printf("Opcion: ");

        scanf("%d", &opc);

        switch(opc){
            case 1:
                printf("\nIngrese el elemento a insertar: ");
                scanf("%d", &x);
                raiz = altaAVL(raiz, x, &exito);
                getchar();
                getchar();
                break;

            case 2:
                printf("\nIngrese el elemento a eliminar: ");
                scanf("%d", &x);
                raiz = bajaAVL(raiz, x, &exito);
                getchar();
                getchar();
                break;

            case 3:
                treeprint(raiz, 0);
                getchar();
                getchar();
                break;

            case 4:
                print2D(raiz, ESPACIO);
                getchar();
                getchar();

            case 0:
                break;
        }

    }
    
    liberarAVL(raiz);
    printf("Gracias por usar, vuelva prontos!\n");


}