#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define FIN -999

typedef struct{
    int V[MAX+1];
}Lista;

void init(Lista *lista);
void localizar(Lista lista, int x, int *pos, int *exito);
void alta(Lista *lista, int x, int *exito);
void baja(Lista *lista, int x, int *exito);
void mostrar(Lista lista);

int main(){
    Lista lista;
    int opc = 1;
    int exito;
    int x = 0;

    init(&lista);

    while(opc != 0){
        system("clear");
        printf("Lista Secuencial con terminacion dada por contenido\nMAX = %d\n", MAX);
        printf("Tipo: Enteros positivos U {0}\n");
        mostrar(lista);
        printf("Seleccione una opcion:\n");
        printf("1. Insertar un elemento\n");
        printf("2. Eliminar un elemento\n");
        printf("0. Salir\n");
        printf("\nOpcion: ");
        scanf("%d", &opc);
    
        switch(opc){
            case 1:
                printf("\nIngrese elemento a insertar: ");
                scanf("%d", &x);
                alta(&lista, x, &exito);
                getchar();
                getchar();
                break;
            case 2:
                printf("\nIngrese elemento a eliminar: ");
                scanf("%d", &x);
                baja(&lista, x, &exito);
                getchar();
                getchar();
                break;
            case 0: break;
            default: break;
        }

    }
    printf("\nGracias por usar. Vuelva prontos!\n");

    return 0;
}

void init(Lista *lista){
    lista->V[0] = FIN;
}

void localizar(Lista lista, int x, int *pos, int *exito){
    int i = 0;
    while(lista.V[i] != FIN && lista.V[i] != x){
        i++;
    }
    *pos = i;
    *exito = (lista.V[i] != FIN);
}

void alta(Lista *lista, int x, int *exito){
    int pos;
    *exito = 0;
    localizar(*lista, x, &pos, exito);
    if(*exito == 1){
        printf("Ya esta el %d en la lista. Matate y grabalo.\n", x);
    }else if(pos < MAX-1){
        lista->V[pos] = x;
        lista->V[pos+1] = FIN;
        printf("Se inserto el %d B)\n", x);
        *exito = 1;
    }else printf("No hay espacio :'v\n");
}

void baja(Lista *lista, int x, int *exito){
    int pos;
    *exito = 0;
    localizar(*lista, x, &pos, exito);
    if(*exito == 0){
        printf("No se encontro %d en la lista. Matate y grabalo\n", x);
    }else{
        int i = pos;
        while(lista->V[i-1] != FIN){
            lista->V[i] = lista->V[i+1];
            i++;
        }
        printf("Elemento %d eliminado B)\n", x);
        *exito = 1;
    }
}

void mostrar(Lista lista){
    printf("Lista: [ ");
    int i = 0;
    while(lista.V[i] != FIN){
        printf("%d | ", lista.V[i]);
        i++;
    }
    printf("* ");
    printf("]\n");
}