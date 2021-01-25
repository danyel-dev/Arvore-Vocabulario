#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

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

    for (i; frase[i] != '\0'; i++) {
        if (frase[i] == ',' || frase[i] == '\n') {
            if (frase[i] != '\n')
                i = i + 1;

            p_portug[cont] = '\0';
            cont = 0;

            chave *infoMeio = (chave*) malloc(sizeof(chave));
            strcpy((*infoMeio).Palavra, "EOF");
            (*infoMeio).Significados = NULL;
            
            insere_palavra(NULL, Raiz, p_portug, p_ingles, infoMeio);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}

Vocabulario *alocaNo(chave *info, Vocabulario *noEsq, Vocabulario *noCentro) {
    Vocabulario *No = (Vocabulario*) malloc(sizeof(Vocabulario));
    
    (*No).chaveEsq = (chave*) malloc(sizeof(chave));
    (*No).chaveDir = (chave*) malloc(sizeof(chave));

    strcpy((*No).chaveEsq->Palavra, (*info).Palavra);
    (*No).chaveEsq->Significados = copia_dados((*No).chaveEsq->Significados, (*info).Significados);

    strcpy((*No).chaveDir->Palavra, "EOF");
    (*No).chaveDir->Significados = NULL;

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

Vocabulario *adicionaNo(Vocabulario *Raiz, chave *info, Vocabulario *Novo) {
    int n = strcmp((*info).Palavra, (*Raiz).chaveEsq->Palavra);

    if (n > 0) {
        strcpy((*Raiz).chaveDir->Palavra, (*info).Palavra);
        (*Raiz).chaveDir->Significados = copia_dados((*Raiz).chaveDir->Significados, (*info).Significados);
        (*Raiz).dir = Novo;
    } 

    else if (n < 0) {
        strcpy((*Raiz).chaveDir->Palavra, (*Raiz).chaveEsq->Palavra);
        strcpy((*Raiz).chaveEsq->Palavra, (*info).Palavra);
        
        (*Raiz).chaveDir->Significados = copia_dados((*Raiz).chaveDir->Significados, (*Raiz).chaveEsq->Significados);
        
        (*Raiz).chaveEsq->Significados = NULL;
        (*Raiz).chaveEsq->Significados = copia_dados((*Raiz).chaveEsq->Significados, (*info).Significados);
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

listaIngles *insere_lista(listaIngles *Significados, char p_ingles[]) {
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

Vocabulario *quebraNo(Vocabulario **Raiz, Vocabulario *NovoNo, chave *info, chave *infoMeio) {
    Vocabulario *Novo;

    int x = strcmp((*info).Palavra, (**Raiz).chaveDir->Palavra);
    int y = strcmp((*info).Palavra, (**Raiz).chaveEsq->Palavra);
    
    if (x > 0) {
        strcpy((*infoMeio).Palavra, (**Raiz).chaveDir->Palavra);
        (*infoMeio).Significados = copia_dados((*infoMeio).Significados, (**Raiz).chaveDir->Significados);

        chave *info2 = (chave*) malloc(sizeof(chave));
        strcpy((*info2).Palavra, (*info).Palavra); 
        (*info2).Significados = NULL;
        (*info2).Significados = copia_dados((*info2).Significados, (*info).Significados);

        Novo = alocaNo(info2, (**Raiz).dir, NovoNo);
    } 

    else if (y < 0) {
        strcpy((*infoMeio).Palavra, (**Raiz).chaveEsq->Palavra);
        (*infoMeio).Significados = copia_dados((*infoMeio).Significados, (**Raiz).chaveEsq->Significados);

        chave *info2 = (chave*) malloc(sizeof(chave));
        strcpy((*info2).Palavra, (**Raiz).chaveDir->Palavra); 
        (*info2).Significados = NULL;
        (*info2).Significados = copia_dados((*info2).Significados, (**Raiz).chaveDir->Significados);

        Novo = alocaNo(info2, (**Raiz).centro, (**Raiz).dir);
        
        strcpy((**Raiz).chaveEsq->Palavra, (*info).Palavra);
        (**Raiz).chaveEsq->Significados = copia_dados((**Raiz).chaveEsq->Significados, (*info).Significados); 
        (**Raiz).centro = NovoNo;
    }

    else {
        strcpy(infoMeio->Palavra, (*info).Palavra);
        (*infoMeio).Significados = copia_dados((*infoMeio).Significados, (*info).Significados);

        chave *info2 = (chave*) malloc(sizeof(chave));
        strcpy((*info2).Palavra, (**Raiz).chaveDir->Palavra); 
        (*info2).Significados = NULL;
        (*info2).Significados = copia_dados((*info2).Significados, (**Raiz).chaveDir->Significados);


        Novo = alocaNo(info2, NovoNo, (**Raiz).dir);  
    }

    strcpy((**Raiz).chaveDir->Palavra, "EOF");
    (**Raiz).chaveDir->Significados = NULL;
    (**Raiz).nChaves = 1;
    (**Raiz).dir = NULL; 

    return Novo;
}

chave *aloca_chave(char palavra[], char significado[]) {
    chave *info = (chave*) malloc(sizeof(chave));
    
    strcpy((*info).Palavra, palavra); 
    (*info).Significados = NULL;
    (*info).Significados = insere_lista((*info).Significados, significado);

    return info;
} 

Vocabulario *insere_palavra(Vocabulario *pai, Vocabulario **Raiz, char palavra[], char significado[], chave *infoMeio) {
    Vocabulario *novo;
    if (*Raiz == NULL) {
        chave *info = aloca_chave(palavra, significado);
        *Raiz = alocaNo(info, NULL, NULL);
    } else {
        int x = strcmp(palavra, (**Raiz).chaveEsq->Palavra);
        int y = strcmp(palavra, (**Raiz).chaveDir->Palavra);
        
        if (x == 0) {
            (**Raiz).chaveEsq->Significados = insere_lista((**Raiz).chaveEsq->Significados, significado);
            
            novo = NULL;
        } else if (y == 0) {
            (**Raiz).chaveDir->Significados = insere_lista((**Raiz).chaveDir->Significados, significado); 
          
            novo = NULL;
        } else {
            if (folha(*Raiz)) {
                if ((**Raiz).nChaves == 1) {
                    chave *info = aloca_chave(palavra, significado);
                    *Raiz = adicionaNo(*Raiz, info, NULL);
                    novo = NULL;
                } else {
                    chave *info = aloca_chave(palavra, significado);
                    novo = quebraNo(Raiz, NULL, info, infoMeio);

                    if (pai == NULL) {
                        *Raiz = alocaNo(infoMeio, *Raiz, novo);
                        novo = NULL; 
                    }
                }
            }

            else {
                if (x < 0) 
                    novo = insere_palavra(Raiz, &(**Raiz).esq, palavra, significado, infoMeio);
                else if ((**Raiz).nChaves == 1 || y < 0) 
                    novo = insere_palavra(Raiz, &(**Raiz).centro, palavra, significado, infoMeio);
                else 
                    novo = insere_palavra(Raiz, &(**Raiz).dir, palavra, significado, infoMeio);

                if (novo != NULL) {
                    if ((**Raiz).nChaves == 1) {
                        Raiz = adicionaNo(*Raiz, infoMeio, novo);
                        novo = NULL;
                    } else {
                        chave *info = (chave*) malloc(sizeof(chave));

                        strcpy((*info).Palavra, (*infoMeio).Palavra); 
                        (*info).Significados = NULL;
                        (*info).Significados = copia_dados((*info).Significados, (*infoMeio).Significados);
                        
                        novo = quebraNo(Raiz, novo, info, infoMeio);
                    
                        if (pai == NULL) {
                            *Raiz = alocaNo(infoMeio, *Raiz, novo);
                            novo = NULL; 
                        }
                    }
                }
            }
        }

    }

    return novo;
}

void imprime_palavras(Vocabulario *Raiz) {
    if (Raiz != NULL) {
        printf("%s %s %d: ", Raiz->chaveEsq->Palavra, Raiz->chaveDir->Palavra, Raiz->nChaves);
        imprime_lista(Raiz->chaveEsq->Significados);
        imprime_lista(Raiz->chaveDir->Significados);
        printf("\n");
        imprime_palavras(Raiz->esq);
        imprime_palavras(Raiz->centro);
        imprime_palavras(Raiz->dir);
    }
}

void imprime_lista(listaIngles *Significados) {
    listaIngles *aux = Significados;

    while (aux != NULL) {
        printf("%s ", aux->palavra_Engles);
        aux = aux->prox;
    }
}

int busca(Vocabulario *Raiz, char palavra[]) {
    if (Raiz != NULL) {
        int x = strcmp(palavra, Raiz->chaveEsq->Palavra);
        int y = strcmp(palavra, Raiz->chaveDir->Palavra);

        if (x == 0) {
            printf("%s: ", Raiz->chaveEsq->Palavra);
            imprime_lista(Raiz->chaveEsq->Significados);
            return 1;
        } else if (y == 0) {
            printf("%s: ", Raiz->chaveDir->Palavra);
            imprime_lista(Raiz->chaveDir->Significados);
            return 1;
        } else {
            if (x < 0)
                busca(Raiz->esq, palavra);
            else if (y < 0 || Raiz->nChaves == 1)
                busca(Raiz->centro, palavra);
            else if (y > 0)
                busca(Raiz->dir, palavra);
        }
    } else 
        return 0; 
}
