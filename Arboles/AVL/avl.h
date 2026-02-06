#include <malloc.h>
#define ESPACIO 10 // Controla la distancia entre niveles

typedef struct n{
    int valor;
    int altura;
    struct n* izq;
    struct n* der;
}Nodo;

//Gemini
// Estructura auxiliar para la cola (necesaria para BFS)
typedef struct q {
    Nodo* dato;
    struct q* sig;
} Cola;

void treeprint(Nodo *root, int level) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++)
        printf(i == level - 1 ? "|-" : "  ");
    printf("%d\n", root->valor);
    treeprint(root->izq, level + 1);
    treeprint(root->der, level + 1);
}

int getAltura(Nodo* n){
    if(n == NULL) return 0;
    return n->altura;
}

Nodo* crearNodo(int x){
    Nodo* nuevo = (Nodo *)malloc(sizeof(Nodo));
    if(nuevo == NULL) return NULL;
    nuevo->altura = 1;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->valor = x;
    return nuevo;
}

void liberarAVL(Nodo* raiz){
    if(raiz == NULL) return;
    liberarAVL(raiz->izq);
    liberarAVL(raiz->der);
    free(raiz);
}

//utilidad para obtener el maximo entre dos enteros
int max(int a, int b){ return (a > b) ? a : b; }

//factor de balance
int getFactorBalance(Nodo* n){
    if(n == NULL) return 0; //arbol vacio

    //-1 , 0 , 1 | si |factor| = 2 se debe rebalancear
    return getAltura(n->izq) - getAltura(n->der);
}

//Rotacion simple a derecha
Nodo* rotacionDerecha(Nodo* x){
    Nodo* y = x->izq; //el anterior segun inOrden
    Nodo* T2 = y->der;
    
    //Rotacion
    x->izq = T2;
    y->der = x;
    
    //actualizar alturas
    x->altura = max(getAltura(x->izq), getAltura(x->der)) + 1;
    y->altura = max(getAltura(y->izq), getAltura(y->der)) + 1;

    //la raiz del subarbol izquierdo se convierte en la raiz del arbol
    return y;
    
}

Nodo* rotacionIzquierda(Nodo* x){
    Nodo* y = x->der; //siguiente segun inOrden
    Nodo* T2 = y->izq;

    //Rotacion
    x->der = T2;
    y->izq = x;

    //actualizar alturas
    x->altura = max(getAltura(x->izq), getAltura(x->der)) + 1;
    y->altura = max(getAltura(y->izq), getAltura(y->der)) + 1;

    //la raiz del subarbol derecho se convierte en la raiz del arbol
    return y;
}

Nodo* rebalancearAVL(Nodo* raiz){
    //actualizar la altura 
    raiz->altura = 1 + max(getAltura(raiz->izq), getAltura(raiz->der));

    //revisar si se produjo un desbalance
    int balance = getFactorBalance(raiz);

    //Casos de desbalance:
    //Caso 1: hacia izquierda
    if(balance > 1){
        //1a: subarbol izquierdo desbalanceado hacia la derecha
        //caso izq-der -> rotacion doble (izq-der)
        if(getFactorBalance(raiz->izq) < 0){
            raiz->izq = rotacionIzquierda(raiz->izq);
        }
        return rotacionDerecha(raiz);
    }
    
    //Caso 2: hacia derecha 
    if(balance < -1){
        //2a: subarbol derecho desbalanceado hacia la izquierda
        //caso der-izq -> rotacion doble (der-izq)
        if(getFactorBalance(raiz->der) > 0){
            raiz->der = rotacionDerecha(raiz->der);
        }
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

Nodo* altaAVL(Nodo* raiz, int val, int* exito){
    //busqueda
    if(raiz == NULL){
        printf("\nElemento %d insertado\n", val);
        *exito = 1;
        return crearNodo(val);
    } 
    if(raiz->valor > val) raiz->izq = altaAVL(raiz->izq, val, exito);
    else if(raiz->valor < val) raiz->der = altaAVL(raiz->der, val, exito);
    else{
        printf("\nNo se admiten valores repetidos en un AVL\n");
        *exito = 0;
        return raiz;
    }
    
    return rebalancearAVL(raiz);
}

Nodo* bajaAVL(Nodo* raiz, int val, int* exito){
    //busqueda
    if(raiz == NULL){
        printf("\nElemento %d no encontrado\n");
        *exito = 0;
        return raiz;
    }
    if(val < raiz->valor){
        printf("\nyendo a subarbol izquierdo de %d\n", raiz->valor);
        raiz->izq = bajaAVL(raiz->izq, val, exito);
    } 
    else if(val > raiz->valor){
        printf("\nyendo a subarbol derecho de %d\n", raiz->valor);
        raiz->der = bajaAVL(raiz->der, val, exito);
    } 
    else{ //encontrado
        printf("Elemento %d encontrado. Eliminando\n", val);
        //Caso 1: 0 o 1 hijo
        if(raiz->izq == NULL || raiz->der == NULL){
            Nodo *temp = raiz->izq ? raiz->izq : raiz->der;
            if(temp != NULL) printf("%d tiene 1 hijo con valor %d\n", val, temp->valor);
            else printf("%d no tiene hijos\n", val);
            free(raiz);
            printf("Elemento %d eliminado\n", val);
            return temp;
        }

        //Caso 2: 2 hijos
        if(raiz->izq != NULL && raiz->der != NULL){
            printf("%d tiene dos hijos: %d y %d\n", val, raiz->izq, raiz->der);
            //reemplazo por el mayor de los menores
            printf("aplicando politica de reemplazo\n");
            Nodo* reemplazo = raiz->izq;
            while(reemplazo->der != NULL){
                reemplazo = reemplazo->der;
            }
            raiz->valor = reemplazo->valor;
            raiz->izq = bajaAVL(raiz->izq, reemplazo->valor, exito);
        }

        *exito = 1;
        printf("\nElemento %d eliminado.\n", val);
    }

    
    return raiz = rebalancearAVL(raiz);
}

void inOrden(Nodo* raiz){
    if(raiz != NULL){
        inOrden(raiz->izq);
        printf("%d | ");
        inOrden(raiz->der);
    }
}

// Funciones básicas de cola
void encolar(Cola** frente, Cola** final, Nodo* n) {
    if (n == NULL) return;
    Cola* nuevo = (Cola*)malloc(sizeof(Cola));
    nuevo->dato = n;
    nuevo->sig = NULL;
    if (*frente == NULL) {
        *frente = *final = nuevo;
    } else {
        (*final)->sig = nuevo;
        *final = nuevo;
    }
}

Nodo* desencolar(Cola** frente, Cola** final) {
    if (*frente == NULL) return NULL;
    Cola* aux = *frente;
    Nodo* n = aux->dato;
    *frente = (*frente)->sig;
    if (*frente == NULL) *final = NULL;
    free(aux);
    return n;
}

// El barrido por niveles (Breadth-First Search)
void barridoPorNiveles(Nodo* raiz) {
    if (raiz == NULL) {
        printf("Arbol vacio.\n");
        return;
    }

    Cola *frente = NULL, *final = NULL;
    encolar(&frente, &final, raiz);

    printf("Barrido por niveles: ");
    while (frente != NULL) {
        Nodo* actual = desencolar(&frente, &final);
        
        printf("[%d] ", actual->valor);

        // Primero encolamos el hijo izquierdo, luego el derecho
        if (actual->izq != NULL) encolar(&frente, &final, actual->izq);
        if (actual->der != NULL) encolar(&frente, &final, actual->der);
    }
    printf("\n");
}

void print2D(Nodo* raiz, int espacio) {
    // Caso base
    if (raiz == NULL) return;

    // Aumentar la distancia entre niveles
    espacio += ESPACIO;

    // Procesar primero el hijo derecho (irá en la parte superior)
    print2D(raiz->der, espacio);

    // Imprimir el nodo actual después del espacio
    printf("\n");
    for (int i = ESPACIO; i < espacio; i++) printf(" ");
    
    // Imprimimos el valor y su altura para verificar balanceo
    printf("[%d]\n", raiz->valor);

    // Procesar el hijo izquierdo (irá en la parte inferior)
    print2D(raiz->izq, espacio);
}
