#include <stdio.h>
#include <stdlib.h>
#include "L2L.h"

void leerArchivo(L2L *lista){
    FILE *fp = fopen("secuencia.txt", "r");
    Nupla X;
    int exito = 0;
    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    
    while(fscanf(fp, "%d\n", &X.x) == 1){
        alta_L2L(lista, X, &exito);
        if (exito == -1)
            printf("Lista llena, no se pudo insertar %d\n", X.x);
        else if (exito == 0)
            printf("Elemento %d duplicado\n", X.x);
        else
            printf("Elemento %d insertado\n", X.x);
    }

    fclose(fp);
}

int main(){
    L2L lista;
    init_L2L(&lista);

    leerArchivo(&lista);

    mostrarDescriptores(lista);

    int opc;

    while (1) {
        printf("\nSeleccione sublista (0 a %d, -1 para salir): ", lista.ult);

        if (scanf("%d", &opc) != 1) {
            printf("Entrada invalida\n");
            fflush(stdin);
            continue;
        }

        if (opc == -1)
            break;

        if (opc < 0 || opc > lista.ult) {
            printf("Indice fuera de rango\n");
            continue;
        }

        mostrar_LSO(lista.ListaDescriptores[opc].sublista);
    }
    
    return 0;
}
