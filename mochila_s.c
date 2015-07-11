#include "mochila_s.h"

typedef struct mno
{
    Elemento *objeto;
} mNo;

/**
    Estrutura para variavel tipo Mochila; esta se comporta como uma pilha,
    onde cada elemento inserido sera o ultimo a ser removido.
*/
struct mochila
{
    int topo;
    int tamanho;
    mNo itens[NRO_MAX_ELEMS_MOCHILA];
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
    m->topo = -1;

    int i;
    for(i = 0; i < NRO_MAX_ELEMS_MOCHILA; ++i)
        m->itens[i].objeto = NULL;

    return m;
}

int MTamanho(Mochila *m)
{
    return m->tamanho;
}

Elemento *MTopo(Mochila *m)
{
    if(MVazia(m))
        return NULL;
    return m->itens[m->topo].objeto;
}

int MVazia(Mochila *m)
{
    if(m->tamanho == 0)
        return 1;
    return 0;
}

int MCheia(Mochila *m)
{
    if(m->tamanho < NRO_MAX_ELEMS_MOCHILA)
        return 0;
    return 1;
}

void MInserir(Mochila *m, Elemento *elem, int *erro)
{
    m->topo++;

    m->itens[m->topo].objeto = elem;

    *erro = 0;
    m->tamanho++;
}

Elemento *MRemover(Mochila *m)
{
    if(MVazia(m))
        return NULL;

    Elemento *elem = NULL;
    elem = m->itens[m->topo].objeto;

    m->itens[m->topo].objeto = NULL;
    m->topo--;
    m->tamanho--;
    return elem;
}

void MDestruir(Mochila *m)
{
    Elemento *e = NULL;
    int i = 0;
    while(i < NRO_MAX_ELEMS_MOCHILA)
    {
        e = m->itens[i].objeto;
        if(e != NULL)
            DestruirElemento(e);
        ++i;
    }

    m->tamanho = 0;
    m->topo = -1;

    if(m != NULL)
        free(m);
    m = NULL;
}

void MMostrarElem(Mochila *m)
{
    printf("Elemento do topo da mochila: ");
    if(!MVazia(m))
        printf("%s", NomeElemento(m->itens[m->topo].objeto));

    printf("\n");
}
