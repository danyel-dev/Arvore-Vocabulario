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
    while (fgets(frase, 1000, fptr) != NULL) 
        if (frase[0] != '%' && frase[3] != '%') 
            divide_palavras(&Raiz, frase);   

    fim = clock();

    printf("Tempo de inserção na árvore: %d\n\n", (fim - inicio) * 1000000);

    // impressão da árvore
    imprime_palavras(Raiz);
    printf("\n");

    // Busca na árvore
    char palavra[30];

    printf("Digite uma palavra para buscar: ");
    scanf("%s", palavra);

    inicio = clock();
    int n = busca(Raiz, palavra);
    fim = clock();

    printf("\n");
    if (n == 0) 
        printf("palavra não encontrada\n");
    printf("Tempo de busca na árvore: %d\n", (fim - inicio) * 1000000);
    
    return 0;
}
