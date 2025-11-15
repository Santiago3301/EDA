#include <stdio.h>
#include <malloc.h>
#include <string.h>

void swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

void printarr(int arr[], int N){
    for(int i=0; i<N; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* bubbleSort(int arr[], int N, int *swaps, int *compars){
    *swaps = 0;
    *compars = 0;
    int *sorted = malloc(N * sizeof(int));
    sorted = memcpy(sorted, arr, N * sizeof(int));
    for(int i=0; i<N; i++){
        for(int pos=0; pos<N-i-1; pos++){
            if(sorted[pos+1] < sorted[pos]){
                swap(&sorted[pos+1], &sorted[pos]);
                (*swaps)++;
            }
            (*compars)++;
        }
    }

    return sorted;
}

int* selectionSort(int arr[], int N, int *swaps, int *compars){
    *swaps = 0;
    *compars = 0;
    int *sorted = malloc(N * sizeof(int));
    sorted = memcpy(sorted, arr, N * sizeof(int));

    for(int i=0; i<N; i++){
        int minpos = i;
        //buscar el menor en el resto del arreglo
        for(int pos=i+1; pos<N; pos++){
            if(sorted[pos] < sorted[minpos]){
                minpos = pos;
            }
            (*compars)++;
        }
        //si el menor es menor al actual -> swap
        if(sorted[minpos] < sorted[i]){
            swap(&sorted[i], &sorted[minpos]);
            (*swaps)++;
        }
    }

    return sorted;
}

int *insertionSort(int arr[], int N, int *swaps, int *compars){
    *swaps = 0;
    *compars = 0;
    int *sorted = malloc(N * sizeof(int));
    sorted = memcpy(sorted, arr, N * sizeof(int));

    for(int i=1; i<N; i++){
        int pos = i;
        while(pos > 0 && (sorted[pos] < sorted[pos-1])){
            swap(&sorted[pos], &sorted[pos-1]);
            pos--;
            (*swaps)++;
            (*compars)++;
        }
        
    }

    return sorted;
}

int main(){
    int arr[] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    int swaps = 0;
    int compars = 0;
    int N = 20;

    printf("\narreglo desordenado:\n");
    printarr(arr, N);

    int *bubble = bubbleSort(arr, N, &swaps, &compars);
    printf("\narreglo ordenado por Bubble Sort:\n");
    printarr(bubble, N);
    printf("intercambios: %d\n", swaps);
    printf("comparaciones: %d\n", compars);

    int *selection = selectionSort(arr, N, &swaps, &compars);
    printf("\narreglo ordenado por Selection Sort:\n");
    printarr(selection, N);
    printf("intercambios: %d\n", swaps);
    printf("comparaciones: %d\n", compars);

    int *insertion = insertionSort(arr, N, &swaps, &compars);
    printf("\narreglo ordenado por Insertion Sort:\n");
    printarr(insertion, N);
    printf("intercambios: %d\n", swaps);
    printf("comparaciones: %d\n", compars);

    free(bubble);
    free(selection);
    free(insertion);
    return 0;
}