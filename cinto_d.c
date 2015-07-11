#include "cinto_d.h"

typedef struct cno
{
    Elemento *objeto;
    int peso;        /* peso do objeto de cada espaco do cinto (maximo = 7 kg) */
    struct cno *prox;
} cNo;

/**
    Estrutura para variavel tipo Cinto dinamico.
    Ela se comporta como uma lista armazenando e removendo os objetos sem
    se importar com a ordem de chegada de cada objeto.
    */
struct cinto
{
    cNo *inicio;
    cNo *fim;
    int tamanho;
};

Cinto *CCriar(int *erro)
{
    Cinto *c = (Cinto *)malloc(sizeof(Cinto));
    if(c == NULL){
        *erro = 1;  /* memoria insuficiente */
        return NULL;
    }
    *erro = 0;
    srand(time(NULL));
    c->inicio = c->fim = NULL;

    cNo *n;
    int i;
    for(i = 0; i < NRO_MAX_ELEMS; ++i) /* criacao de todos os nos */
    {
        n = (cNo *)malloc(sizeof(cNo));
        if(n == NULL){
            *erro = 1;  /* memoria insuficiente */
            return NULL;
        }

        n->objeto = NULL;
        n->prox = NULL;
        n->peso = (rand() % 7) + 1;  /* numero aleatorio de 1 a 7 */

        if(c->inicio == NULL)     /* primeiro elemento */
            c->inicio = c->fim = n;
        else {
            c->fim->prox = n;
            c->fim = n;
        }
    }

    c->tamanho = 0;
    return c;
}

int CTamanho(Cinto *c)
{
    return c->tamanho;
}

int CVazio(Cinto *c)
{
    if(c->tamanho == 0)
        return 1;
    return 0;
}

int CCheio(Cinto *c)
{
    if(c->tamanho < NRO_MAX_ELEMS)
        return 0;
    return 1;
}

void CInserir(Cinto *c, Elemento *elem, int pos, int *erro)
{
    if(CCheio(c)){
        *erro = 1;  /* lista cheia */
        DestruirElemento(elem);
        return;
    }
    *erro = 0;

    cNo *n;
    int pno, pelem, indice = 0;
    pelem = PesoElemento(elem);

    n = c->inicio;
    while(n != NULL && indice < pos)
    {
        indice++;
        pno = n->peso;

        if(indice == pos){
            if(n->objeto == NULL){
                if(pelem <= pno){
                    n->objeto = elem;
                    printf("\nElemento inserido no cinto.");
                    c->tamanho++;
                }
                else
                    printf("\nPeso do elemento eh maior do que o do bolso.");
            }
            else
                printf("\nPosicao ja contem um elemento.\n");
            break;
        }
        n = n->prox;
    }

    if(n == NULL){
        printf("\nNao existe espaco no cinto para este elemento.");
        DestruirElemento(elem);
    }
}

Elemento *CRemover(Cinto *c, char *nome_elem)
{
    if(CVazio(c))
        return NULL;

    Elemento *elem = NULL;

    cNo *n;
    for(n = c->inicio; n != NULL; n = n->prox)
    {
        if(strcmp(NomeElemento(n->objeto), nome_elem) == 0){
            elem = n->objeto;
            n->objeto = NULL;
            break;
        }
    }

    if(n == NULL){
        printf("\nElemento nao esta no cinto.");
        return NULL;
    }

    c->tamanho--;
    return elem;
}

void CDestruir(Cinto *c)
{
    cNo *n = c->inicio;
    while(n != NULL)
    {
        c->inicio = n->prox;

        if(n->objeto != NULL)
            DestruirElemento(n->objeto);

        free(n);
        n = c->inicio;
    }
    c->fim = NULL;
    c->tamanho = 0;
    free(c);
    c = NULL;
}

void CMostrarElem(Cinto *c)
{
    cNo *n = c->inicio;

    printf("\nElementos e pesos do cinto:\n");
    printf("----------------------------\n");
    while(n != NULL)
    {
        if(n->objeto == NULL)
            printf(" %s.......... %d\n", "vazio", n->peso);
        else
            printf(" %s.......... %d\n", NomeElemento(n->objeto), n->peso);
        n = n->prox;
    }
    printf("----------------------------\n\n");
}
