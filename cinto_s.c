#include "cinto_s.h"

typedef struct cno
{
    Elemento *objeto;
    int peso;
} cNo;

/**
    Estrutura para variavel tipo Cinto estatico.
    Ela se comporta como uma lista armazenando e removendo os objetos sem
    se importar com a ordem de chegada de cada objeto.
    */
struct cinto
{
    int inicio;
    int fim;
    int tamanho;
    cNo itens[NRO_MAX_ELEMS];
};

Cinto *CCriar(int *erro)
{
    Cinto *c = (Cinto *)malloc(sizeof(Cinto));
    if(c == NULL){
        *erro = 1;
        return NULL;
    }
    *erro = 0;
    srand(time(NULL));

    c->inicio = 0;
    c->fim = NRO_MAX_ELEMS - 1;
    c->tamanho = 0;

    int i;
    for(i = c->inicio; i < NRO_MAX_ELEMS; ++i)
    {
        c->itens[i].objeto = NULL;
        c->itens[i].peso = (rand() % 7) + 1;
    }
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
        *erro = 1;
        DestruirElemento(elem);
        return;
    }
    *erro = 0;

    cNo *n = NULL;
    int pno, pelem, i, indice = 0;
    pelem = PesoElemento(elem);

    i = c->inicio;
    while(i <= c->fim && indice < pos)
    {
        n = &(c->itens[i]);
        indice++;
        pno = n->peso;

        if(indice == pos){
            if(n->objeto == NULL){
                if(pelem <= pno){
                    n->objeto = elem;
                    printf("\nElemento inserido no cinto.");
                    c->tamanho++;
                }
                else{
                    printf("\nPeso do elemento eh maior do que o do bolso.");
                    DestruirElemento(elem);
                }
            }
            else{
                printf("\nPosicao ja contem um elemento.\n");
                DestruirElemento(elem);
            }
            break;
        }
        ++i;
    }

    if(i > c->fim){
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
    int i;
    for(i = c->inicio; i <= c->fim; i++)
    {
        n = &(c->itens[i]);
        if(strcmp(NomeElemento(n->objeto), nome_elem) == 0){
            elem = n->objeto;
            n->objeto = NULL;
            break;
        }
    }

    if(i > c->fim){
        printf("\nElemento nao esta no cinto.");
        return NULL;
    }

    c->tamanho--;
    return elem;
}

void CDestruir(Cinto *c)
{
    int i;
    cNo *n = NULL;
    for(i = c->inicio; i <= c->fim; ++i)
    {
        n = &(c->itens[i]);
        if(n->objeto != NULL){
            DestruirElemento(n->objeto);
            n->objeto = NULL;
        }
    }

    if(c != NULL)
        free(c);
    c = NULL;
}

void CMostrarElem(Cinto *c)
{
    int i = c->inicio;
    cNo *n;

    printf("\nElementos e pesos do cinto:\n");
    printf("----------------------------\n");
    while(i <= c->fim)
    {
        n = &(c->itens[i]);
        if(n->objeto == NULL)
            printf(" %s.......... %d\n", "vazio", n->peso);
        else
            printf(" %s.......... %d\n", NomeElemento(n->objeto), n->peso);
        ++i;
    }
    printf("----------------------------\n\n");
}
