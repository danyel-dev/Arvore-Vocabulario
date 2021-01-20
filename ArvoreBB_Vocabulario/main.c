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

    printf("Tempo de inserção em nanosegundos: %d\n\n", (fim - inicio) * 1000000);

    // impressão da árvore
    imprimeArv(Raiz);
    printf("\n");

    // Busca na árvore
    char palavra[30];
    printf("Digite uma palavra para buscar: ");
    scanf("%s", &palavra);
    
    inicio = clock();
    int i = busca(Raiz, palavra);
    fim = clock();

    if (i == 0) 
        printf("Palavra não encontrada\n");
    
    printf("\nTempo da busca em nanosegundos: %d\n", (fim - inicio) * 1000000);

    // exclusão na árvore
    printf("\nDigite uma palavra para excluir: ");
    scanf("%s", &palavra);
    
    excluir_palavra(&Raiz, palavra);

    // impressão da árvore
    imprimeArv(Raiz);
    printf("\n");

    return 0;
}
