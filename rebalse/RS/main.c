#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include "estudiante.h"
#include "lista_vinculada.h"
#include "tabla_hash.h"
#include <string.h>

#define MAX 50

#define upper_margin_left 218
#define upper_margin_right 191
#define lower_margin_left 192
#define lower_margin_right 217
#define upwards_T 193
#define downwards_T 194
#define leftwards_T 180
#define rightwards_T 195
#define horizontal_line 196
#define vertical_line 179

void codigoToMayus(char cod[]){
    for(int i = 0; cod[i] != '\0'; i++) {
        cod[i] = toupper((unsigned char) cod[i]);
    }
}

void memorizacion(TablaHash *tabla_hash, int *exito, int *cant){
    FILE* fp = fopen("Alumnos.txt", "r");
    *cant = 0;
    int iter = 0;
    char buffer[256];
    if(fp != NULL && !feof(fp)){
        Estudiante aux;
        rewind(fp);
        while(1){
            if(fscanf(fp,"%7s\n", &aux.codigo) != 1) break;
            aux.codigo[strcspn(aux.codigo, "\n")] = '\0';
            codigoToMayus(aux.codigo);
            if(fscanf(fp,"%80[^,], %80[^\n]\n", aux.apellido, aux.nombre) != 2) break;
            if (fgets(aux.correo, sizeof(aux.correo), fp) == NULL) break;
            aux.correo[strcspn(aux.correo, "\n")] = '\0';
            if (fscanf(fp, "%f\n", &aux.nota) != 1) break;
            if (fgets(aux.condicion, sizeof(aux.condicion), fp) == NULL) break;
            aux.condicion[strcspn(aux.condicion, "\n")] = '\0';
            alta_tabla_hash(tabla_hash,aux,exito, cant);
            if(*exito != 1) printf("(%d) No se pudo cargar el estudiante\n", iter);
            else{
                printf("(%d) Estudiante cargado. Cant: %d\n",iter, *cant);
                //mostrarEstudiante(aux);
            }
            iter++;
        }
        printf("Se cargaron %d estudiantes\n", *cant);
        fclose(fp);
        *exito = 1;
    }else{int h = 0;
        printf("No se encontro el archivo Alumnos.txt\n");
        system("pause");
        *exito = 0;
    }
}

void mostrarEstructura_short(TablaHash t){
    for(int i=0;i<MAX;i++){
        if(i/10 == 0) printf("[ 0%d ] --> ", i);
        else printf("[ %d ] --> ", i);
        reset_lista_vinculada(&t.tabla[i]);
        while(!isOos_lista_vinculada(t.tabla[i])){
            printf(" %s --> ", t.tabla[i].cur->e.apellido);
            forward_lista_vinculada(&t.tabla[i]);
        }
        printf(" NULL\n");
     }
}

void mostrarEstructura_long(TablaHash t){
    int j, aux;
    Estudiante eaux;
    for(int i=0;i<MAX;i++){
        if(isEmpty_lista_vinculada(t.tabla[i])){
            if(i/10 == 0) printf("[ 0%d ]%c%c%c%c%c%c> ", i, horizontal_line,horizontal_line,horizontal_line,horizontal_line,horizontal_line);
            else printf("[ %d ]%c%c%c%c%c%c> ", i, horizontal_line,horizontal_line,horizontal_line,horizontal_line,horizontal_line);
            printf("[               NULL                 ]\n");
            //printf("[    ]\n");
        }
        else{
            if(i<10) printf("[ 0%d ]%c%c%c%c%c%c> ", i,horizontal_line, horizontal_line,horizontal_line,horizontal_line, downwards_T,horizontal_line);
            else printf("[ %d ]%c%c%c%c%c%c> ", i,horizontal_line,horizontal_line,horizontal_line, horizontal_line,downwards_T,horizontal_line);
            reset_lista_vinculada(&t.tabla[i]);
            while(1){
                copy_lista_vinculada(t.tabla[i], &eaux);
                printf("%c                                    %c\n", upper_margin_left, upper_margin_right);
                printf("[    ]    %c   %c Codigo: %s                    %c\n",vertical_line, vertical_line,t.tabla[i].cur->e.codigo,vertical_line);
                //Apellido
                printf("[    ]    %c   %c Apellido: %s",vertical_line, vertical_line, t.tabla[i].cur->e.apellido);
                for(j=0; j < (25 - strlen(eaux.apellido)); j++) printf(" ");
                printf("%c\n", vertical_line);
                //Nombre
                printf("[    ]    %c   %c Nombre: %s",vertical_line, vertical_line, t.tabla[i].cur->e.nombre);
                for(j=0; j < (27 - strlen(eaux.nombre)); j++) printf(" ");
                printf("%c\n", vertical_line);
                //Correo
                printf("[    ]    %c   %c Correo: %s",vertical_line, vertical_line, t.tabla[i].cur->e.correo);
                for(j=0; j < (27 - strlen(eaux.correo)); j++) printf(" ");
                printf("%c\n", vertical_line);
                //Nota
                printf("[    ]    %c   %c Nota: %.2f",vertical_line, vertical_line, t.tabla[i].cur->e.nota);
                if(eaux.nota == 10) aux = 24;
                else aux = 25;
                for(j=0; j < aux; j++) printf(" ");
                printf("%c\n", vertical_line);
                //Condicion
                printf("[    ]    %c   %c Condicion: %s",vertical_line, vertical_line, t.tabla[i].cur->e.condicion);
                for(j=0; j < (24 - strlen(eaux.condicion)); j++) printf(" ");
                printf("%c\n", vertical_line);
                printf("[    ]    %c   %c                                    %c\n",vertical_line,lower_margin_left, lower_margin_right, t.tabla[i].cur->e.codigo);
                printf("[    ]    %c\n", vertical_line);
                //printf(" %s --> ", t.tabla[i].cur->e.apellido);
                forward_lista_vinculada(&t.tabla[i]);
                if(isOos_lista_vinculada(t.tabla[i])){
                    printf("[    ]    %c%c> [               NULL                 ]\n", lower_margin_left, horizontal_line);
                    //printf("[    ]\n");
                    break;
                } else printf("[    ]    %c%c> ", rightwards_T, horizontal_line);
            }
        }
        //printf("[    ]\n");
     }
}


int main(){
    TablaHash tabla_hash;
    int exito, cant = 0;
    init_tabla_hash(&tabla_hash);
    int opc = 1;
    int c;
    char buffer[81];
    Estudiante aux;
    while(opc){
        system("cls");
        printf(">>------------------- > TABLA DE HASH < -------------------<<\n");
        printf(">>                                                         <<\n");
        printf(">>>> 1. Ingresar alumno                                    <<\n");
        printf(">>                                                         <<\n");
        printf(">>>> 2. Eliminar alumno                                    <<\n");
        printf(">>                                                         <<\n");
        printf(">>>> 3. Memorizacion previa                                <<\n");
        printf(">>                                                         <<\n");
        printf(">>>> 4. Mostrar estructura                                 <<\n");
        printf(">>                                                         <<\n");
        printf(">>>> 5. Consultar alumno                                   <<\n");
        printf(">>                                                         <<\n");
        printf(">>>> 6. Modificar alumno                                   <<\n");
        printf(">>                                                         <<\n");
        printf(">>>> 0. Salir                                              <<\n");
        printf(">>                                                         <<\n");
        printf(">>---------------------------------------------------------<<\n");
        printf(">>---------------------------------------------------------<<\n");
        printf(">>>>Opcion: ");
        scanf("%d", &opc);
        switch(opc){
            case 1:
                system("cls");
                printf(">>------------------ > Ingresar alumno < ------------------<<\n");
                printf("Ingrese el apellido: ");
                while(getchar() != '\n');
                scanf("%[^\n]", buffer);
                strcpy(aux.apellido, buffer);
                printf("Ingrese el nombre: ");
                while(getchar() != '\n');
                scanf("%[^\n]", buffer);
                strcpy(aux.nombre, buffer);
                while ((c = getchar()) != '\n' && c != EOF);
                do {
                    printf("Ingrese Condicion final: ");
                    scanf("%[^\n]", buffer);
                }   while(getchar() != '\n' || (strcmp(buffer, "Promociona") && strcmp(buffer, "Regular") && strcmp(buffer, "Libre") && strcmp(buffer, "Ausente")));
                if(!strcmp(buffer,"Ausente")){
                    aux.nota =0;
                } else {
                    do {
                        printf("Ingrese Nota (Entre 0 y 10): ");
                        scanf("%f", &aux.nota);
                    } while(getchar() != '\n' || aux.nota < 0 || aux.nota > 10);
                }
                strcpy(aux.condicion, buffer);
                printf("Ingrese el codigo: ");
                scanf(" %7s", aux.codigo);
                codigoToMayus(aux.codigo);
                strcpy(buffer, aux.codigo);
                while ((c = getchar()) != '\n' && c != EOF);
                do {
                    printf("Ingrese el mail: ");
                    scanf(" %23s", aux.correo);
                    if(strchr(aux.correo, '@') == NULL || strchr(aux.correo, '.') == NULL) {
                        printf("Mail invalido\n");
                    }
                } while(getchar() != '\n' || (strchr(aux.correo, '@') == NULL || strchr(aux.correo, '.') == NULL));
                alta_tabla_hash(&tabla_hash,aux,&exito, &cant);
                if(exito == 1) printf("Estudiante cargado\n");
                else if(exito == 0) printf("No se pudo cargar el estudiante\n");
                else if(exito == -1) printf("No se pudo asignar memoria para el estudiante\n");
                system("pause");
                break;
            case 2: 
                if(cant == 0) printf("\nNo hay estudiantes cargados\n");
                else{                              
                    system("cls");
                    printf(">>------------------ > Eliminar alumno < ------------------<<\n");
                    printf("\nIngrese el codigo del estudiante a eliminar: ");
                    scanf(" %7s", buffer);
                    codigoToMayus(buffer);
                    baja_tabla_hash(&tabla_hash, buffer, &exito, &cant);
                    if(exito) printf("\nEstudiante eliminado\n");
                    else printf("\nEl estudiante no se encuentra cargado.\n");
                }
                system("pause");
                break;

            case 3: 
                memorizacion(&tabla_hash, &exito, &cant);
                system("pause");
                break;
            case 4:
                if(cant == 0) printf("\nNo hay estudiantes cargados\n");
                else{
                    printf("\nSeleccione el modo de muestra:\n");
                    printf("1. Extensa\n2. Resumida\nOpcion: ");
                    scanf("%d", &c);
                    while(c != 1 && c != 2){
                        printf("\nEntrada invalida\n");
                        scanf("%d", &c);
                    }
                    if(c == 1) mostrarEstructura_long(tabla_hash);
                        else mostrarEstructura_short(tabla_hash);
                    }
                system("pause");
                break;
            case 5:
                if(cant == 0) printf("\nNo hay estudiantes cargados\n");
                else{
                    system("cls");
                    printf(">>------------------ > Consultar alumno < ------------------<<\n");
                    printf("\nIngrese el codigo del estudiante a mostrar: ");
                    scanf(" %7s", buffer);
                    codigoToMayus(buffer);
                    evocacion_tabla_hash(tabla_hash,buffer,&exito,&aux);
                    if(exito) mostrarEstudiante(aux);
                    else printf("\nNo se encontro estudiante con codigo %s.\n", buffer);
                }
                system("pause");
                break;

            case 6:
                if(cant == 0) printf("\nNo hay estudiantes cargados\n");
                else{
                    system("cls");                 
                    printf(">>------------------ > Modificar alumno < ------------------<<\n");
                    printf("\nIngrese el codigo del estudiante a modificar: ");
                    scanf(" %7s", buffer);
                    codigoToMayus(buffer);
                    modificar_tabla_hash(&tabla_hash, buffer, &exito);
                    if(exito == 1) printf("Estructura actualizada.\n");
                    else if(exito == 0) printf("\nNo se encontro estudiante con codigo %s.", buffer);
                    else printf("\nNo se realizaron modificaciones.\n");
                }
                system("pause");
            case 0: break;
            default:
                printf("Opcion no valida o funcion en proceso\n");
                system("pause");
                break;    
        }
    }

    return 0;
}