#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>

// int main(int argc, char *argv[]) {
//     if (argc > 0) { // Verifica se pelo menos o nome do programa foi passado
//         // Imprime o primeiro caractere do nome do programa
//         printf("%c\n", argv[0][0]);
//     } else {
//         // Caso nenhum argumento seja passado
//         printf("Nenhum argumento passado.\n");
//     }
//     return 0;
// }

int main(int argc, char *argv[]){
    bool **m = malloc(10*sizeof(bool*));
    for (int i=0; i<10; i++)
        m[i]=calloc(10, sizeof(bool));
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++)
            printf("%d", m[i][j]);
        puts("");
    }
    
}