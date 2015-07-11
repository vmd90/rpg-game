#include "mochila_d.h"

typedef struct mno
{
    Elemento *objeto;
    struct mno *prox;
} mNo;

/**
    Estrutura para variavel tipo Mochila; esta se comporta como uma pilha,
    onde cada elemento inserido sera o ultimo a ser removido.
*/
struct mochila
{
    mNo *topo;
    int tamanho;
};

Mochila *MCriar(int *erro)
{
    Mochila *m = (Mochila *) malloc(sizeof(Mochila));
    if(m == NULL){
        *erro = 1;   /* memoria insuficiente */
        return NULL;
    }
    *erro = 0;
    m->tamanho = 0;
    m->topo = NULL;
    return m;
}

int MTamanho(Mochila *m)
{
    return m->tamanho;
}

Elemento *MTopo(Mochila *m)
{
    return m->topo->objeto;
}

int MVazia(Mochila *m)
{
    if(m->tamanho == 0)
        return 1;
    return 0;
}

void MInserir(Mochila *m, Elemento *elem, int *erro)
{
    mNo *n = (mNo *)malloc(sizeof(mNo));
    if(n == NULL){
        *erro = 1;  /* memoria insuficiente */
        return;
    }

    *erro = 0;
    n->objeto = elem;
    m->tamanho++;
    n->prox = m->topo;
    m->topo = n;
}

Elemento *MRemover(Mochila *m)
{
    if(MVazia(m))
        return NULL;

    Elemento *elem = NULL;
    mNo *n = m->topo;

    m->topo = n->prox;
    m->tamanho--;

    elem = n->objeto;
    free(n);
    return elem;
}

void MDestruir(Mochila *m)
{
    if(MVazia(m)){
        if(m != NULL)
            free(m);
        m = NULL;
        return;
    }

    mNo *n = m->topo;
    while(m->topo != NULL)
    {
        m->topo = n->prox;
        DestruirElemento(n->objeto);
        free(n);
        n = m->topo;
    }

    m->tamanho = 0;

    if(m != NULL)
        free(m);
    m = NULL;
}

void MMostrarElem(Mochila *m)
{
    printf("Elemento do topo da mochila: ");
    if(m->topo != NULL)
        printf("%s", NomeElemento(m->topo->objeto));

    printf("\n");
}



