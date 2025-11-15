#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include<stdio.h>
#include<string.h>

typedef struct {
    //char codigo[8];
    char codigo[8];
    char apellido[81];
    char nombre[81];
    char correo[23];
    char condicion[11];
    float nota;
} Estudiante;

void mostrarEstudiante(Estudiante e){
    printf("Codigo: %s\n", e.codigo);
    printf("Apellido: %s\nNombre: %s\n", e.apellido,e.nombre);
    printf("Correo: %s\n", e.correo);
    printf("Nota: %.2f\n", e.nota);
    printf("Condicion: %s\n", e.condicion);
}
#endif // ESTUDIANTE_H