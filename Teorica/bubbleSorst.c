#include<stdio.h>
void bubbleSort(int arr[], int n){
    int aux, trocou=1;
    for (int i=0; i<n-1 && trocou; i++){
        trocou=0;
        for (int j=0; j<n-1-i; j++)
            if (arr[j]>arr[j+1]){
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
                trocou=1;
            } 
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

    bubbleSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}