#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct listaIngles listaIngles;
typedef struct Vocabulario Vocabulario;

struct listaIngles {
    char palavraEn[30];
    listaIngles *prox;
};

struct Vocabulario {
    char palavraPt[30];
    listaIngles *significados;
    Vocabulario *esq, *dir;
};


void divide_palavras(Vocabulario **Raiz, char frase[]);

void insere_palavra(Vocabulario **Raiz, char p_portug[], char p_ingles[]);

Vocabulario *aloca(char p_portug[], char p_ingles[]);

listaIngles *insere_lista(listaIngles *significado, char p_ingles[]);

void imprimeArv(Vocabulario *Raiz);

void imprime_lista(listaIngles *significados);


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

int busca(Vocabulario *Raiz, char frase[]) {
    int i = 0;

    if (Raiz != NULL) {
        int n = strcmp(frase, Raiz->palavraPt);
        
        if (n < 0)
            busca((*Raiz).esq, frase);
        else if (n > 0)
            busca((*Raiz).dir, frase);
        else {
            printf("%s: ", (*Raiz).palavraPt);
            imprime_lista((*Raiz).significados);
            i = 1;
        }
    } else 
        return i; 
}

void divide_palavras(Vocabulario **Raiz, char frase[]) {
    int cont = 0, i;
    char p_ingles[30], p_portug[30];

    for (i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == ':')
            break;
        p_ingles[i] = frase[i]; 
    }

    p_ingles[i] = '\0';

    i = i + 2;

    for (i; frase[i] != '\0'; ++i) {
        if (frase[i] == ',' || frase[i] == '\n') {
            if (frase[i] != '\n')
                i = i + 1;

            p_portug[cont] = '\0';
            cont = 0;
            insere_palavra(Raiz, p_portug, p_ingles);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}

Vocabulario *aloca(char p_portug[], char p_ingles[]) {
    Vocabulario *No = (Vocabulario*) malloc(sizeof(Vocabulario));
    strcpy((*No).palavraPt, p_portug);
    (*No).esq = NULL;
    (*No).dir = NULL;
    (*No).significados = NULL;
    (*No).significados = insere_lista((*No).significados, p_ingles);
    
    return No;
}

listaIngles *insere_lista(listaIngles *significados, char p_ingles[]) {
    listaIngles *No = (listaIngles*) malloc(sizeof(listaIngles));
    strcpy((*No).palavraEn, p_ingles);
    (*No).prox = NULL;    
    
    if (significados == NULL) 
        return No;
    else {
        listaIngles *aux = significados;

        while (aux->prox != NULL) 
            aux = aux->prox;

        aux->prox = No;
        return significados;
    } 
}

void insere_palavra(Vocabulario **Raiz, char p_portug[], char p_ingles[]) {
    if (*Raiz == NULL) {
        *Raiz = aloca(p_portug, p_ingles);
    } else {
        int n = strcmp(p_portug, (**Raiz).palavraPt);

        if (n < 0) 
            insere_palavra(&(**Raiz).esq, p_portug, p_ingles); 

        else if (n > 0)
            insere_palavra(&(**Raiz).dir, p_portug, p_ingles);

        else 
            (**Raiz).significados = insere_lista((**Raiz).significados, p_ingles);
    }
}

void imprimeArv(Vocabulario *Raiz) {
    if (Raiz != NULL) {
        printf("%s: ", Raiz->palavraPt);
        imprime_lista((*Raiz).significados);
        imprimeArv(Raiz->esq);
        imprimeArv(Raiz->dir);
    }
}

void imprime_lista(listaIngles *significados) {
    for (listaIngles *aux = significados; aux != NULL; aux = aux->prox)
        printf("%s ", aux->palavraEn);
    printf("\n");
}

int qtd_filhos(Vocabulario *Raiz) {
    if (Raiz->esq == NULL && Raiz->dir == NULL) 
        return 0;
    if (Raiz->esq != NULL && Raiz->dir != NULL) 
        return 1;
    if (Raiz->esq != NULL)
        return 2;
    else 
        return 3;
}

Vocabulario *menorfilho(Vocabulario **Raiz) {
    Vocabulario *menor;

    if((**Raiz).esq != NULL)
        menor = menorfilho(&(**Raiz).esq);
    else 
        menor = *Raiz;
    
    return menor;
}

void excluir_palavra(Vocabulario **Raiz, char palavra[]) {  
    if (*Raiz != NULL) {
        int n = strcmp(palavra, (**Raiz).palavraPt);

        if (n < 0) 
            excluir_palavra(&(**Raiz).esq, palavra);

        else if (n > 0) 
            excluir_palavra(&(**Raiz).dir, palavra);
        
        else {
            Vocabulario *aux;
            aux = *Raiz;

            if (qtd_filhos(*Raiz) == 0)
                *Raiz = NULL;

            else if (qtd_filhos(*Raiz) == 2) 
                *Raiz = (**Raiz).esq;

            else if (qtd_filhos(*Raiz) == 3) 
                *Raiz = (**Raiz).dir;

            else if (qtd_filhos(*Raiz) == 1) {
                Vocabulario *menor;
                menor = menorfilho(&(**Raiz).dir);
                menor->esq = (**Raiz).esq;
                *Raiz = (**Raiz).dir;
            }

            free(aux);
        }
    } 
}
