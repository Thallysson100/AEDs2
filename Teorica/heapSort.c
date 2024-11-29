#include <stdlib.h>
#include <stdio.h>
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapfy(int arr[], int n, int i){
    int esq = (i<<1)+1; //filho a esquerda de i
    int dir = (i<<1)+2;
    int max=i, trocou=1;
    while (trocou){
        trocou = 0;
        if (esq<n && arr[esq] > arr[i])
            max = esq;
        if (dir<n && arr[dir] > arr[max])
            max = dir;
        if (max != i){
            trocou = 1;
            swap(arr + i, arr + max);
            i = max;
        }
        esq = (i<<1)+1;
        dir = (i<<1)+2;
    }
    
        
}
void heapSort(int arr[], int n){
    //torna o vetor uma maxheap
    //n/2-1 é o nó mais a direita possível um nível acima das folhas
    for (int i = n/2-1; i >= 0; i--)
        heapfy(arr, n, i);
    for (int i=n-1; i > 0; i--){
        swap(arr, arr+i);
        heapfy(arr, i, 0);
    }
}
void printArray(int arr[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%4d ", arr[i]);
    }
    printf("\n");
}
int main(){
    int arr[] = { 66, 30, 27, 13, 25, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array (size %d): \n", n);
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}