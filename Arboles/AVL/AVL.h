/*
NOTAS:
Implementacion de AVL con ayuda del libro
Data Structures and Program Design in C - Kruse, Leung, Tondo
*/

typedef enum BalanceFactor{
    LH, //desbalance hacia izq
    EH, //balanceado
    RH  //desbalance hacia der
}BalanceFactor;

typedef struct n{
    int valor;
    int altura;
    struct n* izq;
    struct n* der;
}Nodo;

