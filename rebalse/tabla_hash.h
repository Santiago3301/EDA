#ifndef TABLA_HASH_H
#define TABLA_HASH_H
#include "lista_vinculada.h"
#include <malloc.h>

#define MAX 50

typedef struct{
    lista_vinculada tabla[MAX];
    int ult;
}TablaHash;

void init_tabla_hash(TablaHash *t){
    t->ult = -1;

    for(int i=0; i<MAX; i++){
        init_lista_vinculada(&t->tabla[i]);
    }
}

/*
int hash(int code){
    int li = 1000, ls = 9999;
    return ((code - li) * MAX) / (ls - li + 1);
}
*/

int hash(char code[]){
    /*
    int inf = 361, sup = 396;
    int h = 0;
    for(int i=0; code[i] != '\0'; i++){
        //h+=code[i];
        h = h*31 + code[i];
    }
    */
    //return ((h - inf) * MAX) / (sup - inf +1);
    int h = atoi(code);
    return h % MAX;
}

/*
void localizar_tabla_hash(TablaHash t, int code, int *exito){
    //int index = hash(code);
    localizar_lista_vinculada(t.tabla[hash(code)], code, exito);
}
*/

void alta_tabla_hash(TablaHash *t, Estudiante e, int *exito, int *cant){
    int index = hash(e.codigo);
    //printf("h(%d): %d\ncargando\n", e.codigo, index);
    alta_lista_vinculada(&t->tabla[index],e,exito);
    if(*exito) (*cant)++;
    //else printf("no se pudo dar de alta en la lista\n");
}

void baja_tabla_hash(TablaHash *t, char code[], int *exito, int *cant){
    int index = hash(code);
    baja_lista_vinculada(&t->tabla[index],code,exito);
    if(exito) (*cant)++;
}

void evocacion_tabla_hash(TablaHash t, char code[], int *exito, Estudiante *e){
    int index = hash(code);
    localizar_lista_vinculada(&t.tabla[index], code, exito);
    if(*exito) *e = t.tabla[index].cur->e;
    else *exito = 0;
}

void modificar_tabla_hash(TablaHash *t, char code[], int* exito){
    int index = hash(code), modified = 0;
    char buffer[81], c;
    localizar_lista_vinculada(&t->tabla[index], code, exito);
    if(*exito == -1 || exito == 0) *exito = 0;
    else{
        while(buffer[0] != '0'){
            system("cls");
            printf(">>------------------ > Modificar alumno < ------------------<<\n");
            mostrarEstudiante(t->tabla[index].cur->e);
            printf("\nN: Nombre\nA: Apellido\nC: Correo\nP: Calificacion\nF: Condicion final\nIngrese el campo que desea modificar (INGRESE 0 PARA SALIR): ");
            scanf("%s", buffer);
            switch(buffer[0]){
                case 'n':
                case 'N':
                    printf("Ingrese el nuevo nombre: ");
                    while(getchar() != '\n');
                    scanf("%[^\n]", buffer);
                    strcpy(t->tabla[index].cur->e.nombre, buffer);
                    system("pause");
                    modified = 1;
                    break;
                case 'p':
                case 'P':
                    do{
                        printf("Ingrese nota (entre 0 y 10): ");
                        scanf("%f", &t->tabla[index].cur->e.nota);
                    }while(getchar() != '\n' || t->tabla[index].cur->e.nota < 0 || t->tabla[index].acc->e.nota > 10);
                    modified = 1;
                    break;
                case 'a':
                case 'A':
                    printf("Ingrese el nuevo apellido: ");
                    while(getchar() != '\n');
                    scanf("%[^\n]", buffer);
                    strcpy(t->tabla[index].cur->e.apellido, buffer);
                    modified = 1;
                    break;
                case 'c':
                case 'C':
                    do{
                        printf("Ingrese mail: ");
                        scanf(" %23s", buffer);
                        if(strchr(buffer, '@') == NULL || strchr(buffer, '.') == NULL) printf("Mail invalido\n");
                    }while(getchar() != '\n' || (strchr(buffer, '@') == NULL || strchr(buffer, '.') == NULL));
                    strcpy(t->tabla[index].cur->e.correo, buffer);
                    modified = 1;
                    break;
                case 'f':
                case 'F':
                    while ((c = getchar()) != '\n' && c != EOF);
                    do{
                        printf("Ingrese la nueva condicion final: ");
                        scanf("%[^\n]", buffer);
                    }while(getchar() != '\n' || (strcmp(buffer, "Promociona") && strcmp(buffer, "Regular") && strcmp(buffer, "Libre") && strcmp(buffer, "Ausente")));
                    strcpy(t->tabla[index].cur->e.condicion, buffer);
                    modified = 1;
                    break;
                case '0':
                    if(!modified) *exito = -1;
                    else *exito = 1;
                    break;
            }
        }
        
    }
}

#endif // TABLAHASH_H