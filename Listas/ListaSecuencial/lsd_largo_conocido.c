#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int V[MAX];
    int ult;
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
        printf("Lista Secuencial!\nTipo: Numeros Enteros\nMAX = %d\n", MAX);
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
    lista->ult = -1;
    for(int i=0; i<MAX ; i++){
        lista->V[i] = -999;
    }
}

void localizar(Lista lista, int x, int *pos, int *exito){
    *pos = 0;
    while(*pos <= lista.ult && lista.V[*pos] != x){
        *pos += 1;
    }
    *exito = (lista.V[*pos] == x);
}

void alta(Lista *lista, int x, int *exito){
    int pos;
    *exito = 0;
    localizar(*lista, x, &pos, exito);
    if(*exito == 1){
        printf("Ya esta el %d en la lista. Matate y grabalo.\n", x);
    }else if(lista->ult < MAX-1){
        lista->V[pos] = x;
        lista->ult += 1;
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
        lista->V[pos] = lista->V[lista->ult];
        lista->ult -= 1;
        printf("Elemento %d eliminado B)\n", x);
        *exito = 1;
    }
}

void mostrar(Lista lista){
    printf("Lista: [ ");
    int i = 0;
    while(i < lista.ult){
        printf("%d | ", lista.V[i]);
        i++;
    }
    if(lista.ult > -1) printf("%d ", lista.V[lista.ult]);
    printf("]\n");
}