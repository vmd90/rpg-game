#include "mapa.h"

/** Estrutura  caixa possui dois campos (tipo e info) que guardam a informacao de
    cada bloco do tipo caixa e tres ponteiros para tres possiveis sublistas */
struct caixa
{
    eTipoCaixa tipo;  /* determina qual eh o tipo que sera usado no campo info */

    union {
        Elemento *elem;
        Inimigo *inim;
    } info;

    struct caixa *prox;
};

/** Estrutura mapa que possui dois campos para o inicio e o fim de uma lista
    de blocos do tipo caixa e um inteiro para indicar o nivel */
struct mapa
{
    Caixa *inicio;
    Caixa *fim;
    int tamanho;
};

Mapa *MapaCriar(int *erro)
{
    Mapa *map = (Mapa *)malloc(sizeof(Mapa));
    if(map == NULL){
        *erro = 1;  /* memoria insuficiente */
        return NULL;
    }

    *erro = 0;
    map->inicio = map->fim = NULL;
    map->tamanho = 0;
    return map;
}

void MapaDestruir(Mapa *map)
{
    if(map == NULL) /* mapa nao criado */
        return;

    Caixa *c = map->inicio;
    while(c != NULL)    /* destruindo cada bloco */
    {
        map->inicio = c->prox;

        if(c->tipo == ELEM)
            DestruirElemento(c->info.elem);
        else if(c->tipo == INIMIGO)
            DestruirInimigo(c->info.inim);

        free(c);
        c = map->inicio;
    }

    if(map != NULL)
        free(map);
    map = NULL;
}

Caixa *CriarCaixa(eTipoCaixa tipo, int *erro)
{
    int nome, r = 0;

    Caixa *c = (Caixa *)malloc(sizeof(Caixa));
    if(c == NULL){
        *erro = 1;  /* Memoria insuficiente */
        return NULL;
    }

    *erro = 0;
    c->prox = NULL;
    c->tipo = tipo;

    r = (abs(rand()) % 100) + 1;  /* 1 a 100; sorteio para elementos */
    if(r <= 25)
        nome = VARINHA;
    else if(r > 25 && r <= 50)
        nome = ARCO_FLECHA;
    else if(r > 50 && r <= 65)
        nome = FACA;
    else if(r > 65 && r <= 75)
        nome = REVOLVER;
    else if(r > 75 && r <= 85)
        nome = PVIDA;
    else if(r > 85 && r <= 95)
        nome = PSUPER;
    else
        nome = METRALHADORA;

    switch(tipo)
    {
        case VAZIO:    /* info eh vazio */
            break;

        case ELEM:   /* info eh elemento */
            if(r > 75 && r <= 95)
                c->info.elem = CriarElemento(POCAO, nome, erro);
            else
                c->info.elem = CriarElemento(ARMA, nome, erro);

            break;

        case INIMIGO: /* info eh inimigo */
            c->info.inim = CriarInimigo(CriarNomeInimigo(nivel_jogo), 0, 0, nivel_jogo, erro);
            break;
    }
    return c;
}

eTipoCaixa TipoCaixa(Caixa *c)
{
    return (c->tipo);
}

Elemento *InfoElem(Caixa *c)
{
    return (c->info.elem);
}

Inimigo *InfoInim(Caixa *c)
{
    return(c->info.inim);
}

void MapaInserir(Mapa *map, eTipoCaixa tipo, int *erro)
{
    Caixa *c = CriarCaixa(tipo, erro);
    if(*erro)   /* memoria insuficiente */
        return;

    map->tamanho++;

    if(map->inicio == NULL)  /* caso mapa ainda esteja vazio */
        map->inicio = map->fim = c;
    else {
        map->fim->prox = c;
        map->fim = c;
    }
}

void MapaRemover(Mapa *map, int pos)
{
    Caixa *c = map->inicio;
    int i = 1;

    while(i < pos)
    {
        c = c->prox;
        ++i;
    }

    c->tipo = VAZIO;
}

void MapaMostrar(Mapa *map)
{
    printf("\n-----------------\n Nivel %d\n-----------------\n", nivel_jogo);

    Caixa *c = map->inicio;
    int num_caixas = 0;

    printf("\n\n");
    while(num_caixas < map->tamanho)
    {
        printf(".-----. ");
        num_caixas++;
    }

    printf("\n");
    num_caixas = 0;
    while(c != NULL && num_caixas < map->tamanho)
    {
        printf("|  ");
        if(c->tipo == ELEM)
            printf("E");
        else if(c->tipo == INIMIGO)
            printf("I");
        else         /* VAZIO */
            printf(" ");

        printf("  | ");
        num_caixas++;
        c = c->prox;
    }

    printf("\n");
    num_caixas = 0;
    while(num_caixas < map->tamanho)
    {
        printf("._____. ");
        num_caixas++;
    }
    printf("\n");
}

int MapaTamanho(Mapa *map)
{
    if(map != NULL)
        return (map->tamanho);
    return 0;
}

Caixa *MapaPercorrer(Mapa *map, int pos)
{
    if(map == NULL)
        return NULL;

    Caixa *c = map->inicio;
    int i = 1;

    while(i < pos)
    {
        c = c->prox;
        ++i;
    }
    return c;
}

void MapaCriarNivel1(Mapa **map, int *erro)
{
    *map = MapaCriar(erro);  /* Criando mapa 1 */
    if(*map == NULL){
        *erro = 1;
        return;
    }

    *erro = 0;

    /* Inserindo caixas */
    MapaInserir(*map, VAZIO, erro);
    if(*erro)
        return;

    MapaInserir(*map, ELEM, erro);
    if(*erro)
        return;

    MapaInserir(*map, ELEM, erro);
    if(*erro)
        return;

    MapaInserir(*map, INIMIGO, erro);
    if(*erro)
        return;

    MapaInserir(*map, VAZIO, erro);
    if(*erro)
        return;

    MapaInserir(*map, ELEM, erro);
    if(*erro)
        return;

    MapaInserir(*map, INIMIGO, erro);
    if(*erro)
        return;
}

void MapaCriarNivel2(Mapa **map, int *erro)
{
    *map = MapaCriar(erro);
    if(*map == NULL){
        *erro = 1;
        return;
    }

    *erro = 0;

    /* Inserindo caixas */
    MapaInserir(*map, VAZIO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, ELEM, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, INIMIGO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, VAZIO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, INIMIGO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, ELEM, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, ELEM, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, VAZIO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, INIMIGO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, INIMIGO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, ELEM, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, INIMIGO, erro);
    if(*erro)
        return;

    /* Inserindo caixas */
    MapaInserir(*map, VAZIO, erro);
    if(*erro)
        return;
}
