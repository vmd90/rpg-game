#include "mapa.h"

int main()
{
    int erro = 0, pos = 1, pos_cinto = 0;
    char ch = '1';
    char nome_jog[20];
    char nome_elem[20];
    memset(nome_jog, 0, 20);

    printf("*********************\n*                   *\n");
    printf("*       RPG GAME    *\n*                   *\n");
    printf("*********************\n\n");
    printf("Digite seu nome para iniciar: ");

    scanf("%s", nome_jog);
    system("clear");     /* limpar a tela */

    Heroi *h = Inicializar(nome_jog, &erro);
    if(erro){
        printf("Erro: memoria insuficiente");
        return 1;
    }

    Mochila *moch = MochilaHeroi(h);
    Cinto *cint = CintoHeroi(h);

    Mapa *map = NULL;  /* ponteiro para o mapa atual */
    int mapa_criado = 0;  /* verifica se um mapa foi criado */
    nivel_jogo = 1;

    Elemento *elem;
    eTipoElem tipo_elem;

    do
    {
        system("clear");

        /* criacao dos mapas de acordo com o nivel do jogo */
        if(nivel_jogo == 1){
            if(!mapa_criado){
                MapaCriarNivel1(&map, &erro);
                if(erro){
                    printf("Erro: memoria insuficiente\n");
                    break;
                }
                mapa_criado = 1;
            }
        }
        else if(nivel_jogo == 2){
            if(!mapa_criado){
                MapaCriarNivel2(&map, &erro);
                if(erro){
                    printf("Erro: memoria insuficiente\n");
                    break;
                }
                mapa_criado = 1;
            }
        }

        MapaMostrar(map);   /* Mostrar o mapa 1*/
        printf("\n%s esta na posicao: %d", NomeHeroi(h), pos);
        printf("\nPontos de vida: %d\n", VidasHeroi(h));
        CMostrarElem(cint);  /* Mostrar o cinto */
        MMostrarElem(moch);  /* Mostrar o topo da mochila */

        printf("\nEscolha uma das opcoes abaixo:\n");
        printf("[1] - Mover uma posicao.\n");
        printf("[2] - Usar ou remover elemento do cinto.\n");
        printf("[3] - Usar ou remover elemento da mochila.\n");
        printf("[4] - Sair do jogo.\n");

        scanf("%c", &ch);
        switch(ch)
        {
            case '1':  /* mover uma posicao no mapa */
                ++pos;
                Caixa *c = MapaPercorrer(map, pos);
                eTipoCaixa tipo = TipoCaixa(c);
                char ch2 = '0';

                scanf("%c", &ch2);
                if(tipo == ELEM){     /* caso encontre um elemento */
                    printf("Voce encontrou elemento: %s - peso: %d\n", NomeElemento(InfoElem(c)), PesoElemento(InfoElem(c)));
                    printf("O que voce vai fazer:\n");
                    printf("[1] - Adicionar na mochila.\n");
                    printf("[2] - Adicionar no cinto.\n");
                    printf("[3] - Ignorar.\n");

                    scanf("%c", &ch2);
                    switch(ch2)
                    {
                        case '1':
                            MInserir(moch, InfoElem(c), &erro); /* Inserindo na mochila*/
                            if(erro){
                                printf("Erro: memoria insuficiente");
                                system("sleep 4s");
                                MapaDestruir(map);
                                DestruirHeroi(h);
                                return 1;
                            }
                            break;

                        case '2':
                            printf("\nQual lugar do cinto (1 a 5): ");
                            scanf("%d", &pos_cinto);
                            CInserir(cint, InfoElem(c), pos_cinto, &erro);
                            if(erro){
                                printf("\nErro: Cinto esta cheio.\n");
                                system("sleep 4s");
                                DestruirElemento(InfoElem(c));
                                elem = NULL;
                            }
                            break;

                        default:
                            DestruirElemento(InfoElem(c));
                            elem = NULL;
                            break;
                    }
                }
                else if(tipo == INIMIGO){ /* caso encontre um inimigo */
                    printf("\nBATALHA com %s!\nVoce quer usar alguma arma?\n", NomeInimigo(InfoInim(c)));
                    printf("[1] - Pegar da mochila\n");
                    printf("[2] - Pegar do cinto\n");
                    printf("[3] - Nao usar nada\n");

                    scanf("%c", &ch2);
                    switch(ch2)
                    {
                        case '1':
                            elem = MRemover(moch);
                            break;
                        case '2':
                            printf("\nDigite o nome do elemento: ");
                            scanf("%s", nome_elem);
                            elem = CRemover(cint, nome_elem);
                            break;
                        default:
                            DestruirElemento(elem);
                            elem = NULL;
                            break;
                    }
                    printf("\nElemento usado: %s.\n", (elem == NULL ? "nenhum" : NomeElemento(elem)));
                    system("sleep 4s");
                    srand(time(NULL));

                    /* Inicio da BATALHA */
                    Inimigo *i = InfoInim(c);
                    int heroi_vidas = VidasHeroi(h);
                    int inim_vidas = VidasInimigo(InfoInim(c));
                    int jog = rand() % 2;        /* decide quem inicia o ataque */
                    int acertou = 0;  /* decide se um acertou o outro */

                    while(heroi_vidas > 0 && inim_vidas > 0)
                    {
                        acertou = rand() % 2;
                        if(jog == 0){  /* heroi ataca */
                            if(acertou){
                                printf("Voce acertou.\n");
                                ModificarVidasInimigo(i, -1*(10 + InfoAtaque(elem)));
                            }
                            else
                                printf("Voce errou.\n");
                            jog = 1;  /* vez do inimigo atacar */
                        }
                        else {   /* inimigo ataca */
                            if(acertou){
                                printf("%s acertou\n", NomeInimigo(i));
                                ModificarVidasHeroi(h, -1*AtaqueInimigo(i));
                            }
                            else
                                printf("%s errou.\n", NomeInimigo(i));
                            jog = 0;
                        }

                        heroi_vidas = VidasHeroi(h);
                        inim_vidas = VidasInimigo(InfoInim(c));
                    }

                    if(heroi_vidas <= 0){  /* jogo terminou */
                        printf("\nVoce perdeu o jogo.\n");
                        MapaDestruir(map);
                        DestruirHeroi(h);
                        system("sleep 4s");
                        return 0;
                    }

                    if(inim_vidas <= 0){
                        printf("\nVoce venceu o %s.\n", NomeInimigo(i));
                        system("sleep 4s");
                    }
                }
                MapaRemover(map, pos);  /* Remove do mapa 1*/
                break;

            case '2':    /* usar ou descartar um elemento do cinto */
                memset(nome_elem, 0, 20);
                printf("\nDigite o nome do elemento: ");
                scanf("%s", nome_elem);
                elem = CRemover(cint, nome_elem);
                if(elem == NULL){
                    printf("\nElemento nao encontrado no cinto!\n");
                    system("sleep 4s");
                    break;
                }

                tipo_elem = TipoElem(elem);

                if(tipo_elem == POCAO)  /* uso de pocao */
                    ModificarVidasHeroi(h, InfoCura(elem));
                DestruirElemento(elem);  /* descarte do elemento */
                elem = NULL;
                break;

            case '3':  /* usar ou descartar um elemento da mochila */
                elem = MRemover(moch);
                if(elem == NULL){
                    printf("\nMochila esta vazia!\n");
                    system("sleep 4s");
                    break;
                }

                tipo_elem = TipoElem(elem);
                if(tipo_elem == POCAO)   /* uso de pocao */
                    ModificarVidasHeroi(h, InfoCura(elem));
                DestruirElemento(elem);
                elem = NULL;
                break;

            case '4':  /* sair do jogo */
                break;

            default:
                break;
        }

        if(pos == MapaTamanho(map)){  /* heroi chegou na ultima caixa */
            printf("\n Voce venceu o nivel %d!\n", nivel_jogo);
            system("sleep 4s");
            ++nivel_jogo;
            MapaDestruir(map);
            pos = 1;
            mapa_criado = 0;
        }
    }while(ch != '4' && nivel_jogo <= 2);

    DestruirHeroi(h);

    system("sleep 4s");
    return 0;
}
