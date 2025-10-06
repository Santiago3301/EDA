#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "estudiante.h"
#include "rebalse_separado.h"
#include <string.h>

#define MAX 50

const char* upper_margin_right = "┐";
const char* lower_margin_right = "┘";
const char* upper_margin_left = "┌";
const char* lower_margin_left = "└";
const char* upwards_T       = "┴";
const char* downwards_T     = "┬";
const char* leftwards_T     = "┤";
const char* rightwards_T    = "├";
const char* horizontal_line = "─";
const char* vertical_line   = "│";

void codigoToMayus(char cod[]){
    for(int i = 0; cod[i] != '\0'; i++) {
        cod[i] = toupper((unsigned char) cod[i]);
    }
}

void memorizacion(rebalse_separado *rs, int *exito, int *cant){
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
            alta_RS(rs,aux,exito, cant);
            /*if(*exito != 1) printf("(%d) No se pudo cargar el estudiante\n", iter);
            else{
                printf("(%d) Estudiante cargado. Cant: %d\n",iter, *cant);
                //mostrarEstudiante(aux);
            }*/
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

int main(){
    rebalse_separado rs;
    int exito, cant = 0;
    init_RS(&rs);
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
            case 3: memorizacion(&rs,&exito,&cant);
            case 0: break;
            default:
                printf("Opcion no valida o funcion en proceso\n");
                system("pause");
                break;    
        }
    }

    return 0;
}