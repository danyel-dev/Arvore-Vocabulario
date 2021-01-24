#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listaIngles listaIngles;
typedef struct chave chave;
typedef struct Vocabulario Vocabulario;

struct listaIngles {
    char palavra_Engles[30];
    listaIngles *prox;
};

struct chave {
    char Palavra[30];
    listaIngles *Significados;
};

struct Vocabulario {
    chave *chaveEsq, *chaveDir;
    int nChaves; 
    Vocabulario *esq, *centro, *dir;
};


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

            chave *infoMeio = NULL;
            insere_palavra(NULL, Raiz, p_portug, p_ingles, infoMeio);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}


listaIngles *insere_lista(listaIngles *Significados, char p_ingles[]) {
    printf("oi\n");
    listaIngles *No = (listaIngles*) malloc(sizeof(listaIngles));

    strcpy((*No).palavra_Engles, p_ingles);
    (*No).prox = NULL;    
    
    if (Significados == NULL) {
        return No;
    } else {
        listaIngles *aux = Significados;

        while (aux->prox != NULL) 
            aux = aux->prox;

        aux->prox = No;
        return Significados;
    } 
}


Vocabulario *alocaNo(Vocabulario palavra[], char significado[], Vocabulario *noEsq, Vocabulario *noCentro) {
    Vocabulario *No = (Vocabulario*) malloc(sizeof(Vocabulario));
    
    (*No).chaveEsq = (chave*) malloc(sizeof(chave));
    (*No).chaveDir = NULL;

    strcpy((*No).chaveEsq->Palavra, palavra);
    (*No).chaveEsq->Significados = insere_lista((*No).chaveEsq->Significados, significado); 

    (*No).nChaves = 1;
    (*No).esq = noEsq;
    (*No).centro = noCentro;
    (*No).dir = NULL;

    return No;
}


listaIngles *copia_dados(listaIngles *Significados_Dir, listaIngles *Significados_Esq) {
    listaIngles *aux = Significados_Esq;
    Significados_Dir = NULL;

    while (aux != NULL) {
        Significados_Dir = insere_lista(Significados_Dir, aux->palavra_Engles);
        aux = aux->prox;    
    }

    return Significados_Dir;
}


Vocabulario *adicionaNo(Vocabulario *Raiz, char palavra[], char significado[], Vocabulario *Novo) {
    int n = strcmp(palavra, (*Raiz).chaveEsq->Palavra);

    (*Raiz).chaveDir = (chave*) malloc(sizeof(chave));

    if (n > 0) {
        strcpy((*Raiz).chaveDir->Palavra, palavra);
        (*Raiz).chaveDir->Significados = insere_lista((*Raiz).chaveDir->Significados, significado);
        (*Raiz).dir = Novo;
    } 

    else if (n < 0) {
        strcpy((*Raiz).chaveDir->Palavra, (*Raiz).chaveEsq->Palavra);
        strcpy((*Raiz).chaveEsq->Palavra, palavra);
        
        (*Raiz).chaveDir->Significados = copia_dados((*Raiz).chaveDir->Significados, (*Raiz).chaveEsq->Significados);
        
        (*Raiz).chaveEsq->Significados = NULL;
        (*Raiz).chaveEsq->Significados = insere_lista((*Raiz).chaveEsq->Significados, significado);
        (*Raiz).dir = (*Raiz).centro;
        (*Raiz).centro = Novo;
    } 

    (*Raiz).nChaves = 2;
    return Raiz;
}


int folha(Vocabulario *Raiz) {
    int folha = 0;

    if ((*Raiz).esq == NULL && (*Raiz).centro == NULL && (*Raiz).dir == NULL)
        folha = 1;
    
    return folha;
}


void insere_palavra(Vocabulario *pai, Vocabulario **Raiz, char palavra[], char significado[], chave *infoMeio) {
    Vocabulario *novo;

    if (*Raiz == NULL) 
        *Raiz = alocaNo(palavra, significado, NULL, NULL);
    else {
        int x, y;
        x = strcmp(palavra, (**Raiz).chaveEsq->Palavra);
        
        if ((**Raiz).chaveDir != NULL)
            y = strcmp(palavra, (**Raiz).chaveDir->Palavra);
        
        if (x == 0) {
            novo = NULL;
        } 
        
        else if (y == 0) {
            novo = NULL;
        } 
        
        else {
            if (folha(*Raiz)) {
                if ((**Raiz).nChaves == 1) {
                    *Raiz = adicionaNo(*Raiz, palavra, significado, NULL);
                    novo = NULL;
                } 
            }
        } 
    }
    
}
