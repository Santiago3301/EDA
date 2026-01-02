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

int* merge(int *left, int nL, int *right, int nR, int *compars, int *moves) {
    int *res = malloc((nL + nR) * sizeof(int));
    int i = 0, j = 0, k = 0;

    while (i < nL && j < nR) {
        (*compars)++;  // comparación principal
        
        if (left[i] <= right[j]) {
            res[k++] = left[i++];
        } else {
            res[k++] = right[j++];
        }
        (*moves)++; // escribimos en res
    }

    // Copiar lo que queda del lado izquierdo
    while (i < nL) {
        res[k++] = left[i++];
        (*moves)++;
    }

    // Copiar lo que queda del lado derecho
    while (j < nR) {
        res[k++] = right[j++];
        (*moves)++;
    }

    return res;
}

int* mergeSort(int arr[], int N, int *compars, int *moves) {

    if (N == 1) {
        int *single = malloc(sizeof(int));
        single[0] = arr[0];
        (*moves)++; // copiar elemento
        return single;
    }

    int mid = N / 2;

    // copiar mitad izquierda
    int *left  = mergeSort(arr, mid, compars, moves);

    // copiar mitad derecha
    int *right = mergeSort(arr + mid, N - mid, compars, moves);

    // mezclar
    int *merged = merge(left, mid, right, N - mid, compars, moves);

    free(left);
    free(right);

    return merged;
}
int main(){
    int arr[] = {137, 92, 184, 41, 173, 67, 12, 159, 3, 118, 144, 58, 199, 25, 186, 132,
78, 9, 168, 121, 54, 147, 33, 103, 182, 70, 155, 82, 5, 114, 195, 46,
109, 160, 31, 89, 146, 1, 174, 98, 42, 150, 135, 22, 193, 63, 129, 177,
91, 36, 119, 4, 171, 88, 52, 161, 29, 102, 165, 17, 141, 190, 57, 124,
180, 75, 8, 152, 44, 128, 187, 69, 112, 176, 26, 96, 140, 51, 169, 19,
107, 157, 60, 131, 194, 38, 85, 148, 6, 167, 111, 23, 101, 181, 72, 14,
153, 49, 133, 196, 65, 116, 179, 34, 94, 143, 53, 166, 15, 105, 158, 61,
127, 192, 40, 83, 151, 10, 170, 115, 21, 100, 178, 73, 13, 154, 48, 130,
197, 64, 117, 175, 32, 95, 142, 55, 163, 16, 106, 156, 62, 126, 191, 37,
84, 149, 7, 164, 110, 24, 99, 183, 74, 11, 145, 47, 134, 198, 66, 113,
172, 28, 93, 139, 56, 162, 18, 108, 154, 59, 125, 189, 35, 81, 120, 2,
130, 97, 20, 122, 185, 68, 27, 149, 45, 136, 191, 76, 90, 188, 50, 104};
    int swaps = 0;
    int compars = 0;
    int N = sizeof(arr)/sizeof(arr[0]);

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

    int *merge = mergeSort(arr, N, &compars, &swaps);
    printf("\narreglo ordenado por Merge Sort:\n");
    printarr(merge, N);
    printf("intercambios: %d\n", swaps);
    printf("comparaciones: %d\n", compars);

    free(bubble);
    free(selection);
    free(insertion);
    return 0;
}