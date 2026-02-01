#ifndef LSO_H
#define LSO_H
#define MAX_LSO 5

typedef struct {
    int x;
    int y;
} Nupla;

typedef struct {
    Nupla lista[MAX_LSO];
    int ult;
} LSO;

void init_LSO(LSO *lso) {
    lso->ult=-1;
}

void liberar_LSO(LSO *lso){
    lso->ult = -1;
}

void localizar_LSO(LSO l, int x, int *pos, int *exito){
    *exito = 0;
    if(l.ult == -1){
        printf("lista vacia\n");
        *pos = 0;
        return;
    }
    printf("lista no vacia\n");
    int li = 0;
    int ls = l.ult;
    int m = (li+ls)/2;
    while(li <= ls && l.lista[m].x != x){
        if(x < l.lista[m].x) ls = m - 1;
        else li = m + 1;
        m = (li+ls)/2;
    }
    if(li<=ls && l.lista[m].x == x){
        *exito = 1;
        *pos = m;
        printf("%d encontrado en pos %d\n", x, *pos);
    } else {
        printf("localizar %d fallo en pos %d\n", x, li);
        *pos = li;
    }
}

void alta_LSO(LSO *l, Nupla X, int *exito){
    //Caso 1: sublista llena
    if(l->ult == MAX_LSO-1){
        *exito = -1;
        return; 
    }
    int pos = 0;
    localizar_LSO(*l, X.x, &pos, exito);
    printf("pos: %d, exito: %d\n", pos, *exito);
    //Caso 2: x ya existe en la lista
    if(*exito == 1){
        *exito = 0;
        return;
    }
    //Caso 3: No se halló x y hay espacio -> insertar
    for(int i = (l->ult)+1; i>pos; i--){
        l->lista[i] = l->lista[i-1];
    }
    l->lista[pos] = X;
    l->ult += 1;
    *exito = 1;
}

void baja_LSO(LSO *l, int x, int *exito){
    int pos = 0;
    localizar_LSO(*l, x, &pos, exito);
    //Caso 1: x no existe
    if(*exito == 0){
        return;
    }
    //Caso 2: x existe -> eliminar
    for(int i = pos; i<l->ult; i++){
        l->lista[i] = l->lista[i+1];
    }
    l->ult -= 1;
    *exito = 1;
}

void evocar_LSO(LSO l, int x, Nupla *X, int *exito){
    int pos = 0;
    localizar_LSO(l, x, &pos, exito);
    //Caso 1: x no existe
    if(*exito == 0){
        return;
    }
    //Caso 2: x existe -> devolver
    *X = l.lista[pos];
    *exito = 1;
}

void mostrar_LSO(LSO l){
    printf("\n[ x : ");
    for(int i=0; i <= l.ult ; i++){
        printf("%d , ", l.lista[i].x);
    }
    printf(" ]\n");

    printf("[ y : ");
    for(int i=0; i <= l.ult ; i++){
        printf("%d , ", l.lista[i].y);
    }
    printf(" ]\n");
}

#endif //LSO_H