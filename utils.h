#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

// GEMINI: Usamos 'static inline' para que no haya conflictos al incluirlo en varios .c
static inline void clear(int opc) {
    if (opc == 1) {
        system("cls");   // Windows
    } else {
        system("clear"); // Linux / macOS
    }
}

void pause(){
  printf("\nPresione ENTER para continuar...\n");
  getchar();
  getchar();
}

void introduccion_estructuras(int clear_option){
  clear(clear_option);
  printf("Bienvenido!\n");
  printf("Este programa contiene implementaciones y ejemplos simples\n");
  printf("de uso de algunas de las estructuras de datos vistas en la\n");
  printf("materia Estructuras de Datos y Algoritmos, en la Universi-\n");
  printf("dad Nacional de San Luis.\n\n");
  printf("Estas implementaciones fueron realizadas entre los meses de\n");
  printf("enero y febrero de 2026, mientras me estaba preprando para\n");
  printf("rendir el final de la materia.\n\n");
  printf("Cada categoría y estructura tendra una breve introduccion a\n");
  printf("la misma. En el menu principal las podes desactivar.\n\n");
  printf("Gracias por usar. Disfrute su visita!\n\n");
  printf(" -- Santiago Velazquez\n");
  pause();
}

void introduccion_listas(int clear_option){
  clear(clear_option);
  printf("---- > Listas < ----\n\n");
  printf("Una lista es la forma más simple e intuitiva de\n");
  printf("almacenar un conjunto. Consiste de agrupar los\n");
  printf("elementos uno detrás del otro de manera tal que\n");
  printf("cada uno tiene un predecesor y un sucesor, ex-\n");
  printf("cepto por el primer y último elemento, respec-\n");
  printf("tivamente.\n\n");
  printf("Hay dos formas de representar una lista:\n\n");
  printf("- Representacion Secuencial:\n");
  printf("Almacenamos los elementos en celdas contiguas\n");
  printf("de memoria, lo que llamamos <arreglo>.\n");
  printf("En este programa, representamos un arreglo de\n");
  printf("esta forma:\n\n");
  printf("[ a | b | c | ... | z ]\n\n");
  printf("Si no se conoce el largo de la lista, la gra-\n");
  printf("ficamos asi:\n\n");
  printf("[ a | b | ... | x | y | * ]\n\n");
  printf("Donde <*> es la marca de fin de la lista.\n\n");
  printf("- Representacion Vinculada:\n");
  printf("Almacenamos los elementos en direcciones de\n");
  printf("memoria no contiguas, en celdas que llamamos\n");
  printf("<Nodos>. Cada nodo contiene un campo <valor>\n");
  printf("y un apuntador a otro nodo.\n");
  printf("Aquí los representamos de esta forma:\n\n");
  printf("[ valor |o]-->\n\n");
  printf("Una lista vinculada tiene esta forma:\n\n");
  printf("o--> [ a |o]--> [ b |o]--> ... [ z |o]--> Ii.\n\n");
  printf("El simbolo <Ii.> pretende imitar el simbolo de\n");
  printf("tierra electrica. Representa <null>, una di-\n");
  printf("rección de memoria no valida para un nodo.\n");
  printf("La usamos como marca de fin para la lista vinculada.\n");
  pause();
}

#endif
