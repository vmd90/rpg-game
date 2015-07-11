#include "jog.h"
extern int nivel_jogo;

/**
  Estrutura para variavel do tipo Heroi.
*/
struct heroi
{
    int vidas;
    char nome[20];
    Mochila *mochila;
    Cinto *cinto;
};

/**
    Estrutura para variavel do tipo Inimigo.
*/
struct inimigo
{
    int ataque;
    int vidas;
    char nome[20];
};

/**
    Estrutura para uma variavel do tipo Elemento.
    Cada elemento pode ser uma arma ou pocao, sendo que o tipo arma possui
    info.ataque e o tipo cura info.cura.
*/
struct elemento
{
    int peso;
    eTipoElem tipo;
    char nome[20];

    union {
        int ataque;
        int cura;
    } info;
};


Elemento *CriarElemento(eTipoElem elem, int nome, int *erro)
{
    Elemento *objeto = (Elemento *)malloc(sizeof(Elemento));
    if(objeto == NULL){
        *erro = 1;  /* memoria insuficiente */
        return NULL;
    }

    *erro = 0;
    objeto->tipo = elem;

    switch(nome)
    {
        case VARINHA:
            strcpy(objeto->nome, "varinha");
            objeto->peso = 1;
            objeto->info.ataque = 20;
            break;

        case ARCO_FLECHA:
            strcpy(objeto->nome, "arco_flecha");
            objeto->peso = 1;
            objeto->info.ataque = 30;
            break;

        case FACA:
            strcpy(objeto->nome, "faca");
            objeto->peso = 3;
            objeto->info.ataque = 40;
            break;

        case REVOLVER:
            strcpy(objeto->nome, "revolver");
            objeto->peso = 5;
            objeto->info.ataque = 60;
            break;

        case METRALHADORA:
            strcpy(objeto->nome, "metralhadora");
            objeto->peso = 7;
            objeto->info.ataque = 80;
            break;

        case PVIDA:
            strcpy(objeto->nome, "pvida");
            objeto->peso = 3;
            objeto->info.cura = 15;
            break;

        case PSUPER:
            strcpy(objeto->nome, "psuper");
            objeto->peso = 4;
            objeto->info.cura = 50;
            break;
    }
    return objeto;
}

void DestruirElemento(Elemento *elem)
{
    if(elem != NULL)
        free(elem);
    elem = NULL;
}

char *NomeElemento(Elemento *elem)
{
    if(elem != NULL)
        return elem->nome;
    return ("");
}

int PesoElemento(Elemento *elem)
{
    return elem->peso;
}

int InfoAtaque(Elemento *elem)
{
    if(elem != NULL && elem->tipo == ARMA)
        return (elem->info.ataque);
    return 0;
}

int InfoCura(Elemento *elem)
{
    if(elem != NULL && elem->tipo == POCAO)
        return (elem->info.cura);
    return 0;
}

eTipoElem TipoElem(Elemento *elem)
{
    return elem->tipo;
}

/**************************************************************************/

Heroi *Inicializar(char *nome, int *erro)
{
    Heroi *h = (Heroi *)malloc(sizeof(Heroi));
    if(h == NULL){
        *erro = 1;  /* memoria insuficiente */
        return NULL;
    }

    *erro = 0;
    h->vidas = 50;
    memset(h->nome, 0, 20);  /* seta 20 bytes da variavel nome para 0 */
    strcpy(h->nome, nome);

    /* Inicializando cinto */
    Cinto *c = CCriar(erro);
    if(*erro)
        return NULL;  /* memoria insuficiente */

    /* Inicializando mochila */
    Mochila *m = MCriar(erro);
    if(*erro)
        return NULL;  /* memoria insuficiente */

    h->cinto = c;
    h->mochila = m;
    return h;
}

Cinto *CintoHeroi(Heroi *h)
{
    return h->cinto;
}

Mochila *MochilaHeroi(Heroi *h)
{
    return h->mochila;
}

int VidasHeroi(Heroi *h)
{
    return h->vidas;
}

void ModificarVidasHeroi(Heroi *h, int v)
{
    h->vidas += v;
}

char *NomeHeroi(Heroi *h)
{
    return h->nome;
}

void DestruirHeroi(Heroi *h)
{
    if(h == NULL)
        return;

    CDestruir(h->cinto);  /* Destruindo estrutura cinto */
    MDestruir(h->mochila); /* Destruindo estrutura mochila */
    free(h);
    h = NULL;
}

Inimigo *CriarInimigo(char *nome, int ataque, int vidas, int nivel, int *erro)
{
    Inimigo *inim = (Inimigo *)malloc(sizeof(Inimigo));
    if(inim == NULL){
        *erro = 1;   /* memoria insuficiente */
        return NULL;
    }

    *erro = 0;
    inim->ataque = ataque + 10*nivel;
    inim->vidas = vidas + 10*nivel;

    memset(inim->nome, 0, 20);
    strcpy(inim->nome, nome);
    free(nome);
    return inim;
}

char *CriarNomeInimigo()
{
    char *str = (char *)malloc(6*sizeof(char));
    sprintf(str, "Inim%d", nivel_jogo);
    return str;
}

int VidasInimigo(Inimigo *inim)
{
    return inim->vidas;
}

char *NomeInimigo(Inimigo *inim)
{
    return inim->nome;
}

void ModificarVidasInimigo(Inimigo *inim, int v)
{
    inim->vidas += v;
}

int AtaqueInimigo(Inimigo *inim)
{
    return inim->ataque;
}

void DestruirInimigo(Inimigo *inim)
{
    if(inim != NULL)
        free(inim);
    inim = NULL;
}
