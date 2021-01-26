#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

struct listaIngles {
    char palavraEn[30];
    listaIngles *prox;
};

struct Vocabulario {
    char palavraPt[30];
    int altura;
    listaIngles *significados;
    Vocabulario *esq, *dir;
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
            insere_palavra(Raiz, p_portug, p_ingles);
        } 

        else {
            p_portug[cont] = frase[i];    
            cont++;
        }
    }
}

Vocabulario *alocaNo(char p_portug[], char p_ingles[]) {
    Vocabulario *No = (Vocabulario*) malloc(sizeof(Vocabulario));
    
    strcpy((*No).palavraPt, p_portug);
    (*No).esq = NULL;
    (*No).dir = NULL;
    (*No).altura = 0;
    (*No).significados = NULL;
    (*No).significados = insere_lista((*No).significados, p_ingles);
    
    return No;
}

int altura(Vocabulario *Raiz) {
    int alt = -1, e, d;

    if (Raiz != NULL) {
        e = altura(Raiz->esq);
        d = altura(Raiz->dir);

        if (e > d)
            alt = e+1;
        else
            alt = d+1;
    }

    return alt;
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

int insere_palavra(Vocabulario **Raiz, char p_portug[], char p_ingles[]) {
    int inseriu = 1;

	if (*Raiz == NULL)
		*Raiz = alocaNo(p_portug, p_ingles);
	else { 	
	    if (strcmp(p_portug, (*Raiz)->palavraPt) < 0){
		    int fb;
            inseriu = insere_palavra(&(*Raiz)->esq, p_portug, p_ingles);
			
            if (inseriu) {
				fb = altura((**Raiz).esq) - altura((**Raiz).dir);
				
                if (fb >= 2) {
					if (strcmp(p_portug, (*Raiz)->esq->palavraPt) < 0)
						rotate_right(Raiz);
			        else 
                        rotate_LeftRight(Raiz);
				}
			}
		}

		else if (strcmp(p_portug, (*Raiz)->palavraPt) > 0) {
            int fb;
            inseriu = insere_palavra(&(*Raiz)->dir, p_portug, p_ingles);

            if (inseriu) {
                fb = altura((**Raiz).esq) - altura((**Raiz).dir);

                if (fb <= -2) {
                    if (strcmp(p_portug, (*Raiz)->dir->palavraPt) > 0)
                        rotate_left(Raiz);
				    else 
                        rotate_RightLeft(Raiz);
                }
            }
		}

		else {
		    inseriu = 0;
			(**Raiz).significados = insere_lista((**Raiz).significados, p_ingles);
		}
	
        (*Raiz)->altura = altura(*Raiz);
	}
	
	return inseriu;
}

void rotate_right(Vocabulario **Raiz) {
    Vocabulario *no = (**Raiz).esq;
    (**Raiz).esq = no->dir;
    no->dir = *Raiz;
    
    (**Raiz).altura = altura(*Raiz);
    no->altura = altura(no);
    
    *Raiz = no;
}

void rotate_left(Vocabulario **Raiz) {
    Vocabulario *no = (**Raiz).dir;
    (**Raiz).dir = no->esq;
    no->esq = *Raiz;
    
    (**Raiz).altura = altura(*Raiz);
    no->altura = altura(no);
    
    *Raiz = no;
}

void rotate_LeftRight(Vocabulario **Raiz) {
    rotate_left(&(**Raiz).esq);
    rotate_right(Raiz);
}

void rotate_RightLeft(Vocabulario **Raiz) {
    rotate_right(&(**Raiz).dir);
    rotate_left(Raiz);
}

void imprimeArv(Vocabulario *Raiz) {
    if (Raiz != NULL) {
        printf("fb: %d, %s: ", altura(Raiz->esq) - altura(Raiz->dir), Raiz->palavraPt);
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

int busca(Vocabulario *Raiz, char palavra[]) {
    int i = 0;

    if (Raiz != NULL) {
        int n = strcmp(palavra, Raiz->palavraPt);
        
        if (n < 0)
            busca((*Raiz).esq, palavra);
        else if (n > 0)
            busca((*Raiz).dir, palavra);
        else {
            printf("%s: ", (*Raiz).palavraPt);
            imprime_lista((*Raiz).significados);
            i = 1;
        }
    } else 
        return i; 
}

int qtd_filhos(Vocabulario *raiz) {
    int filho = 0; 

    if (raiz->esq != NULL && raiz->dir != NULL) 
        filho = 1; 
    if (raiz->esq != NULL)
        filho = 2; 
    else 
        filho = 3; 

    return filho;
}

Vocabulario *menorfilho(Vocabulario **raiz) {
    Vocabulario *menor;

    if((**raiz).esq != NULL)
        menor = menorfilho(&(**raiz).esq);
    else 
        menor = *raiz;
    
    return menor;
}

int excluir_palavra(Vocabulario **Raiz, char palavra[]) {
	int removeu = 0;

    if (*Raiz != NULL) {
	    if (strcmp(palavra, (**Raiz).palavraPt) < 0) {
			int fb;
	        removeu = excluir_palavra(&(*Raiz)->esq, palavra);
		
            if (removeu) {
				fb = altura((*Raiz)->esq) - altura((*Raiz)->esq);
				
                if (fb >= 2) {
					if (strcmp(palavra, (**Raiz).palavraPt) < 0)
						rotate_right(Raiz);
					else
						rotate_LeftRight(Raiz);
				}
			}
		}

		else if (strcmp(palavra, (**Raiz).palavraPt) > 0){
            int fb;
            removeu = excluir_palavra(&(*Raiz)->dir, palavra);

            if (removeu) {
                fb = altura((**Raiz).esq) - altura((**Raiz).dir);

                if (fb <= -2) {
                    if (strcmp(palavra, (**Raiz).palavraPt) > 0)
                        rotate_left(Raiz);
                    else
                        rotate_RightLeft(Raiz);
                }
            }
        }

		else {
			Vocabulario *aux = *Raiz;

            if (qtd_filhos(*Raiz) == 0)
                *Raiz = NULL;

            else if (qtd_filhos(*Raiz) == 2) 
                *Raiz = (**Raiz).esq;

            else if (qtd_filhos(*Raiz) == 3) 
                *Raiz = (**Raiz).dir;

            else if (qtd_filhos(*Raiz) == 1){
            	Vocabulario *menor = menorfilho(&(**Raiz).dir);
                menor->esq = (**Raiz).esq;
                *Raiz = (**Raiz).dir;
                
                int fb;
                fb = altura((**Raiz).esq) - altura((**Raiz).dir);
				
                if (fb >= 2) {
					if (strcmp(palavra, (**Raiz).palavraPt) < 0)
						rotate_right(Raiz);
					else
						rotate_LeftRight(Raiz);
				}
            }

            free(aux);
		}
    }

    return removeu;
}
