#include <stdio.h>
#include <time.h>
#include "functions.c"

int main() {    
    char frase[1000]; 
    Vocabulario *Raiz = NULL;

    FILE *fptr;
    fptr = fopen("vocabulario.txt", "r");

    clock_t inicio, fim;
    inicio = clock();

    // inserção na árvore
    int cont = 0;
    while (fgets(frase, 1000, fptr) != NULL) {
        if (frase[0] != '%' && frase[3] != '%') {  
            divide_palavras(&Raiz, frase);   
            cont++;
        }

        if (cont == 2) 
            break;
    }

    // printf("%s\n", (*Raiz).chaveDir->Palavra);

    return 0;
}
