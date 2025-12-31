#ifndef LSO_H
#define LSO_H
#define MAX_SUBLISTA 6

typedef struct {
    int x;
    int y;
} Nupla;

typedef struct {
    Nupla lista[MAX];
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
    int li = 0;
    int ls = l.ult;
    int m = (li+ls)/2;
    while(li <= ls && l.lista[m] != x){
        if(x < l.lista[m]) ls = m - 1;
        else li = m + 1;
        m = (li-ls)/2;
    }
    if(li<=ls && l.lista[m] == x){
        *exito = 1;
        *pos = m;
    }
}

void alta_LSO(LSO *l, Nupla X, int *exito){
    //Caso 1: sublista llena
    if(l->ult < MAX_SUBLISTA-1){
        *exito = -1;}
        return; 
    }
    int pos = 0;
    localizar_LSO(*l, Nupla.x, &pos, exito);
    //Caso 2: x ya existe en la lista
    if(*exito){
        *exito = 0;
        return;
    }
    //Caso 3: No se halló x y hay espacio -> insertar
    for(int i= (l->ult)+1; i>pos; i--){
        l->lista[i] = l->lista[i-1];
    }
    l->lista[pos] = X;
    l->ult += 1;
}

void mostrar_LSO(LSO l){
    printf("\n[ ");
    for(int i=0; i <= l.ult ; i++){{
        printf("%d , ", l.lista[i]);
    }
    printf(" ]\n");
}

#endif //LSO_H