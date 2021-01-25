typedef struct listaIngles listaIngles;
typedef struct chave chave;
typedef struct Vocabulario Vocabulario;

void divide_palavras(Vocabulario **Raiz, char frase[]);

Vocabulario *alocaNo(chave *info, Vocabulario *noEsq, Vocabulario *noCentro);

listaIngles *copia_dados(listaIngles *Significados_Dir, listaIngles *Significados_Esq);

Vocabulario *adicionaNo(Vocabulario *Raiz, chave *info, Vocabulario *Novo);

int folha(Vocabulario *Raiz);

listaIngles *insere_lista(listaIngles *Significados, char p_ingles[]);

Vocabulario *quebraNo(Vocabulario **Raiz, Vocabulario *NovoNo, chave *info, chave *infoMeio);

chave *aloca_chave(char palavra[], char significado[]);

Vocabulario *insere_palavra(Vocabulario *pai, Vocabulario **Raiz, char palavra[], char significado[]
, chave *infoMeio);

void imprime_palavras(Vocabulario *Raiz);

void imprime_lista(listaIngles *Significados);

int busca(Vocabulario *Raiz, char palavra[]);
