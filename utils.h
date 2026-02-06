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
  getchar();
  getchar();
}
#endif
