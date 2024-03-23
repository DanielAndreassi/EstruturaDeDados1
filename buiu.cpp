#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <conio2.h>
#include <math.h>
#include <time.h>

// todas os conceitos de pilha estao nos include, pilha normal,listas concorrentes(TADPilhaM1) e pilhas multiplas(TADPilhaM2)
#include "TADPilha.h"
// #include "TadPilhaM1.h"
// #include "TADPilhaM2.h"

int movimentos = 0;

// declarao de funcoes
// auxiliares
void limparPilhaMonteVirado();
int buscaFigura(char figBuscada[3]);
void popularPilhasColunas(TpPilha &monte, TpPilha &p1, TpPilha &p2, TpPilha &p3, TpPilha &p4, TpPilha &p5, TpPilha &p6, TpPilha &p7);

// mover cartas
void destribuirMesa();
void moveMesaTemp();
void moveNaipeMesa(TpPilha &pilhaOuros, TpPilha &pilhaEspadas, TpPilha &pilhaCopas, TpPilha &pilhaPaus, TpPilha &pilhaColuna1, TpPilha &pilhaColuna2, TpPilha &pilhaColuna3, TpPilha &pilhaColuna4, TpPilha &pilhaColuna5, TpPilha &pilhaColuna6, TpPilha &pilhaColuna7);
void moveMesaMesa(TpPilha &pilhaColuna1, TpPilha &pilhaColuna2, TpPilha &pilhaColuna3, TpPilha &pilhaColuna4, TpPilha &pilhaColuna5, TpPilha &pilhaColuna6, TpPilha &pilhaColuna7);
void moveMesaNaipe();
void moveMonteViradoParaNaipe(TpPilha monteVirado, TpPilha &pilhaOuros, TpPilha &pilhaEspadas, TpPilha &pilhaCopas, TpPilha &pilhaPaus);
void moveMonteViradoParaNaipe();
void moveMonteViradoParaMesa();

// verificacoes
int quantasCartasTemNaPilha(TpPilha p);
void pegarCartaOuResetarBaralho(TpPilha &pilhaMonte, TpPilha &pilhaMonteVirado, int &qteCartasPilhaMonte);
int verificaPodeEfeturarjogadaMoveNaipeMesa(TpPilha monteNaipe, TpPilha monteMesa);
int verificaJogadaMesaMesa(TpPilha origem, TpPilha destinho, int qteCartasOrigem);
int verificaGanhou(TpPilha pilhaOuros, TpPilha pilhaEspadas, TpPilha pilhaCopas, TpPilha pilhaPaus);
int verificarMoverMonteParaNaipe(TpPilha monteVirado, TpPilha pilhaOuro, TpPilha pilhaEspadas, TpPilha pilhaCopas, TpPilha pilhaPaus, int monte);

// exibir interface e menu
char submenuMontesNaipe();
void telaInicial();
void executar();
char menuPrincipal(TpPilha pilhaMonte, TpPilha pilhaMonteVirado);
void exibirInterfaceInicial(TpPilha p1, TpPilha p2, TpPilha p3, TpPilha p4, TpPilha p5, TpPilha p6, TpPilha p7);
void inicializarMesa(
    TpPilha &pilhaMonte,
    TpPilha &pilhaMonteVirado,
    TpPilha &pilhaOuros,
    TpPilha &pilhaEspadas,
    TpPilha &pilhaCopas,
    TpPilha &pilhaPaus,
    TpPilha &pilhaColuna1,
    TpPilha &pilhaColuna2,
    TpPilha &pilhaColuna3,
    TpPilha &pilhaColuna4,
    TpPilha &pilhaColuna5,
    TpPilha &pilhaColuna6,
    TpPilha &pilhaColuna7);

void criaBaralho(TpPilha &p);
void embaralhar(tpCarta *baralho, int n);
void limpaMenu();
void contagemDeMovimentos();

// fim das declaracoes de funcoes

void telaInicial()
{
    system("cls");

    // textcolor(WHITE); // Muda a cor do texto para branca

    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::: PACIENCIA ::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\nOBJETIVO:\n\n- Preencher, com a menor quantidade de movimentos possiveis, os 4 naipes disponiveis com as cartas em ordem crescente e do mesmo naipe.\n");
    printf("\nREGRAS:\n");
    printf("\n- As cartas das pilhas da mesa que serao movidas estao mais a direita.");
    printf("\n- Para as cartas serem movidas para as pilhas da mesa elas devem ser de uma cor diferente da que esta na base e na sequencia.");
    printf("\n- Apenas o rei (13) pode ser movido para uma das pilhas vazias da mesa.");
    printf("\n- Cada pilha do temporario comporta apenas uma carta.");
    printf("\n- E possivel mover um bloco de cartas entre as pilhas da mesa desde que todas esteja na sequencia e em cores alternadas.");
    printf("\n- As cartas a serem colocadas nas pilhas dos naipes devem ser da menor para a maior e do mesmo naipe.");
    printf("\n\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");

    printf("\n\n");
    system("pause");
}

void criaBaralho(TpPilha &p)
{
    tpCarta aux[52];
    char figuras[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int naipe[4] = {1, 2, 3, 4};
    int cont = 0;
    // CUIDADO COM MAGIC NUMBERS 13 E 4 SIGNIFICA O QE PRA QUEM LE DE FORA??

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            strcpy(aux[cont].figura, figuras[i]);
            aux[cont].naipe = naipe[j];
            if (naipe[j] % 2 == 0)
            {
                aux[cont].preto = 1;
            }
            else
            {
                aux[cont].preto = 0;
            }
            aux[cont].viradaPraCima = 1;
            cont++;
        }
    }
    srand(time(NULL));
    embaralhar(aux, 52);
    for (int i = 0; i < 52; i++)
    {
        // aux[i];
        // printf("%s\t%d\t%d\n", aux[i].figura, aux[i].naipe, aux[i].preto);
        Push(p, aux[i]);
    }
}

int verificarMoverMonteParaNaipe(TpPilha monteVirado, TpPilha pilhaOuro, TpPilha pilhaEspadas, TpPilha pilhaCopas, TpPilha pilhaPaus, int monte)
{

    tpCarta cartaTopoMonte = Pop(monteVirado);

    if (monte == 1)
    {
        tpCarta aux = Pop(pilhaOuro);
        if ((buscaFigura(cartaTopoMonte.figura) > buscaFigura(aux.figura)) && cartaTopoMonte.preto == aux.preto)
        {
            return 1;
        }
    }
    if (monte == 2)
    {
        tpCarta aux = Pop(pilhaEspadas);
        if ((buscaFigura(cartaTopoMonte.figura) > buscaFigura(aux.figura)) && cartaTopoMonte.preto == aux.preto)
        {
            return 1;
        }
    }
    if (monte == 3)
    {
        tpCarta aux = Pop(pilhaCopas);
        if ((buscaFigura(cartaTopoMonte.figura) > buscaFigura(aux.figura)) && cartaTopoMonte.preto == aux.preto)
        {
            return 1;
        }
    }
    if (monte == 4)
    {

        tpCarta aux = Pop(pilhaPaus);
        if ((buscaFigura(cartaTopoMonte.figura) > buscaFigura(aux.figura)) && cartaTopoMonte.preto == aux.preto)
        {
            return 1;
        }
    }
    return -1;
}

void moveMonteViradoParaNaipe(TpPilha monteVirado, TpPilha &pilhaOuros, TpPilha &pilhaEspadas, TpPilha &pilhaCopas, TpPilha &pilhaPaus)
{
    printf("\nQual monte de naipes desejar mover essa carta (1-4)");

    int monte = scanf("%d", &monte);

    while (monte > 4 && monte < 1)
    {
        printf("O numero do monte digitado nao existe");
        printf("Digite novamente: (1-4)");
        scanf("%d", &monte);
    }
    if (!Vazia(monteVirado.TOPO))
    {
        if (verificarMoverMonteParaNaipe(monteVirado, pilhaOuros, pilhaEspadas, pilhaCopas, pilhaPaus, monte) != -1)
        {
            Push(pilhaPaus, Pop(monteVirado));
        }
        else
        {
            printf("A carta a ser movida deve ser do mesmo naipe e a proxima da sequencia!!");
        }
    }
    else
    {
        printf("Nao a nada no monte virado!!\n");
        gotoxy(1, 18);
        system("pause");
        limpaMenu();
    }
}

void embaralhar(tpCarta *baralho, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        tpCarta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }
}

void popularPilhasColunas(TpPilha &monte, TpPilha &p1, TpPilha &p2, TpPilha &p3, TpPilha &p4, TpPilha &p5, TpPilha &p6, TpPilha &p7)
{
    tpCarta aux;
    Push(p1, Pop(monte));
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p2, aux);
    Push(p2, Pop(monte));
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p3, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p3, aux);
    Push(p3, Pop(monte));
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p4, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p4, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p4, aux);
    Push(p4, Pop(monte));
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p5, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p5, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p5, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p5, aux);
    Push(p5, Pop(monte));
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p6, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p6, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p6, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p6, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p6, aux);
    Push(p6, Pop(monte));
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p7, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p7, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p7, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p7, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p7, aux);
    aux = Pop(monte);
    aux.viradaPraCima = 0;
    Push(p7, aux);
    Push(p7, Pop(monte));
}

void exibirInterfaceInicial(TpPilha p1, TpPilha p2, TpPilha p3, TpPilha p4, TpPilha p5, TpPilha p6, TpPilha p7)
{
    gotoxy(4, 2);
    printf("BARAI");

    // quadrado esquerda em cima branco com naipes
    int colI = 2, colF = 11, linI = 3, linF = 8;
    textbackground(15);
    for (int i = linI; i <= linF; i++)
    {
        for (int j = colI; j <= colF; j++)
        {
            gotoxy(j, i);
            if (j == 6 && i == 5)
            {
                textcolor(4);
                printf("%c", 4);
            }
            else if (j == 7 && i == 5)
            {
                textcolor(0);
                printf("%c", 6);
            }
            else if (j == 6 && i == 6)
            {
                textcolor(4);
                printf("%c", 3);
            }
            else if (j == 7 && i == 6)
            {
                textcolor(0);
                printf("%c", 5);
            }
            // 24 cartas
            else if (j == 6 && i == 8)
            {
                textcolor(0);
                printf("2");
            }
            else if (j == 7 && i == 8)
            {
                textcolor(0);
                printf("4");
            }
            else
            {
                printf(" ");
            }
        }
    }
    textbackground(0);
    textcolor(15);

    // as 7 pilhas de cartas
    gotoxy(14, 2);
    printf("M - 1");
    ExbibirTemporarioSoVerPilha(p1, 14, 3, 1);
    gotoxy(23, 2);
    printf("M - 2");
    ExbibirTemporarioSoVerPilha(p2, 23, 3, 1);
    gotoxy(32, 2);
    printf("M - 3");
    ExbibirTemporarioSoVerPilha(p3, 32, 3, 1);
    gotoxy(41, 2);
    printf("M - 4");
    ExbibirTemporarioSoVerPilha(p4, 41, 3, 1);
    gotoxy(50, 2);
    printf("M - 5");
    ExbibirTemporarioSoVerPilha(p5, 50, 3, 1);
    gotoxy(59, 2);
    printf("M - 6");
    ExbibirTemporarioSoVerPilha(p6, 59, 3, 1);
    gotoxy(68, 2);
    printf("M - 7");
    ExbibirTemporarioSoVerPilha(p7, 68, 3, 1);

    // quatro montes auxiliares

    // col77 para aux
    gotoxy(77, 3);
    printf("-------");
    gotoxy(77, 4);
    printf("|  %c  |", 4);
    gotoxy(77, 5);
    printf("-------");

    gotoxy(77, 6);
    printf("-------");
    gotoxy(77, 7);
    printf("|  %c  |", 6);
    gotoxy(77, 8);
    printf("-------");

    gotoxy(77, 9);
    printf("-------");
    gotoxy(77, 10);
    printf("|  %c  |", 3);
    gotoxy(77, 11);
    printf("-------");

    gotoxy(77, 12);
    printf("-------");
    gotoxy(77, 13);
    printf("|  %c  |", 5);
    gotoxy(77, 14);
    printf("-------");

    // gotoxy(2, 24);
}

char menuPrincipal(TpPilha pilhaMonte, TpPilha pilhaMonteVirado)
{
    // MOVER MESA -> NAIPE
    // MOVER NAIPE -> MESA
    // MOVER MESA -> MESA
    // PEGAR CARTA
    gotoxy(1, 18);
    if (Vazia(pilhaMonte.TOPO) && !Vazia(pilhaMonteVirado.TOPO))
    {
        printf("[A] Embaralhar cartas sem monte no baralho\n");
    }
    else
    {
        printf("[A] Pegar nova carta\n");
    }
    printf("[B] Mover da Mesa para Naipe\n");
    printf("[C] Mover monte Naipe para Mesa\n");
    printf("[D] Mover entre montes da Mesa\n");
    printf("[E] Mover carta do Baralho para Mesa\n");
    printf("[F] Mover carta do Baralho para monte Naipe\n");
    printf("[ESC] Sair\n");
    printf("Opcao desejada: ");
    return toupper(getche());
}

void inicializarMesa(
    TpPilha &pilhaMonte,
    TpPilha &pilhaMonteVirado,
    TpPilha &pilhaOuros,
    TpPilha &pilhaEspadas,
    TpPilha &pilhaCopas,
    TpPilha &pilhaPaus,
    TpPilha &pilhaColuna1,
    TpPilha &pilhaColuna2,
    TpPilha &pilhaColuna3,
    TpPilha &pilhaColuna4,
    TpPilha &pilhaColuna5,
    TpPilha &pilhaColuna6,
    TpPilha &pilhaColuna7,
    int &qteCartasPilhaMonte)
{
    // fazer sistema de pontuação?
    // pode desfazer jogada?
    // CRIAR BARALHO
    criaBaralho(pilhaMonte);
    // POPULAR PILHAS MONTE
    popularPilhasColunas(pilhaMonte, pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7);
    exibirInterfaceInicial(pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7);
    qteCartasPilhaMonte = 24;
}

// MOVER MESA -> NAIPE
// MOVER NAIPE -> MESA
// MOVER MESA -> MESA
// PEGAR CARTA

void moveMesaNaipe()
{
}

char submenuMontesNaipe()
{
    gotoxy(1, 19);
    printf("[A] Monte Ouros\n");
    printf("[B] Monte Espadas\n");
    printf("[C] Monte Copas\n");
    printf("[D] Monte Paus\n");
    printf("Opcao desejada: ");
    return toupper(getche());
}

char submenuMontesColunas(int excluirQual = 0)
{
    if (excluirQual == 0)
    {
        gotoxy(1, 19);
        printf("[A] Monte 1\n");
        printf("[B] Monte 2\n");
        printf("[C] Monte 3\n");
        printf("[D] Monte 4\n");
        printf("[E] Monte 5\n");
        printf("[F] Monte 6\n");
        printf("[G] Monte 7\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
    else if (excluirQual == 1)
    {
        gotoxy(1, 19);
        printf("[B] Monte 2\n");
        printf("[C] Monte 3\n");
        printf("[D] Monte 4\n");
        printf("[E] Monte 5\n");
        printf("[F] Monte 6\n");
        printf("[G] Monte 7\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
    else if (excluirQual == 2)
    {
        gotoxy(1, 19);
        printf("[A] Monte 1\n");
        printf("[C] Monte 3\n");
        printf("[D] Monte 4\n");
        printf("[E] Monte 5\n");
        printf("[F] Monte 6\n");
        printf("[G] Monte 7\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
    else if (excluirQual == 3)
    {
        gotoxy(1, 19);
        printf("[A] Monte 1\n");
        printf("[B] Monte 2\n");
        printf("[D] Monte 4\n");
        printf("[E] Monte 5\n");
        printf("[F] Monte 6\n");
        printf("[G] Monte 7\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
    else if (excluirQual == 4)
    {
        gotoxy(1, 19);
        printf("[A] Monte 1\n");
        printf("[B] Monte 2\n");
        printf("[C] Monte 3\n");
        printf("[E] Monte 5\n");
        printf("[F] Monte 6\n");
        printf("[G] Monte 7\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
    else if (excluirQual == 5)
    {
        gotoxy(1, 19);
        printf("[A] Monte 1\n");
        printf("[B] Monte 2\n");
        printf("[C] Monte 3\n");
        printf("[D] Monte 4\n");
        printf("[F] Monte 6\n");
        printf("[G] Monte 7\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
    else if (excluirQual == 6)
    {
        gotoxy(1, 19);
        printf("[A] Monte 1\n");
        printf("[B] Monte 2\n");
        printf("[C] Monte 3\n");
        printf("[D] Monte 4\n");
        printf("[E] Monte 5\n");
        printf("[G] Monte 7\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
    else if (excluirQual == 7)
    {
        gotoxy(1, 19);
        printf("[A] Monte 1\n");
        printf("[B] Monte 2\n");
        printf("[C] Monte 3\n");
        printf("[D] Monte 4\n");
        printf("[E] Monte 5\n");
        printf("[F] Monte 6\n");
        printf("Opcao desejada: ");
        return toupper(getche());
    }
}

void limparPilhaColuna(int numPilha)
{
    int colI, colF, linI = 3, linF = 15;
    switch (numPilha)
    {
    case 1:
        colI = 14;
        break;
    case 2:
        colI = 23;
        break;
    case 3:
        colI = 32;
        break;
    case 4:
        colI = 41;
        break;
    case 5:
        colI = 50;
        break;
    case 6:
        colI = 59;
        break;
    case 7:
        colI = 68;
        break;
    default:
        break;
    }
    colF = colI + 7;
    for (int i = linI; i <= linF; i++)
    {
        for (int j = colI; j <= colF; j++)
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
}

void limparPilhaNaipe(int numPilha)
{
    int colI = 77, colF = 83, linI, linF;
    if (numPilha == 1)
    {
        linI = 3;
        linF = 5;
    }
    else if (numPilha == 2)
    {
        linI = 6;
        linF = 8;
    }
    else if (numPilha == 3)
    {
        linI = 9;
        linF = 11;
    }
    else if (numPilha == 4)
    {
        linI = 12;
        linF = 14;
    }
    for (int i = linI; i <= linF; i++)
    {
        for (int j = colI; j <= colF; j++)
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
}

void moveNaipeMesa(TpPilha &pilhaOuros, TpPilha &pilhaEspadas, TpPilha &pilhaCopas, TpPilha &pilhaPaus, TpPilha &pilhaColuna1, TpPilha &pilhaColuna2, TpPilha &pilhaColuna3, TpPilha &pilhaColuna4, TpPilha &pilhaColuna5, TpPilha &pilhaColuna6, TpPilha &pilhaColuna7)
{
    limpaMenu();
    gotoxy(1, 18);
    printf("Mover de: ");
    char opMoverPara, opMoverDe = submenuMontesNaipe();
    switch (opMoverDe)
    {
    case 'A':
        // ESCOLHEU MONTE OUROS
        limpaMenu();
        gotoxy(1, 18);
        printf("Para: ");
        opMoverPara = submenuMontesColunas();
        switch (opMoverPara)
        {
        case 'A':
            // ESCOLHEU MONTE 1
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaOuros, pilhaColuna1))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaOuros
                tpCarta aux = Pop(pilhaOuros);
                // limpar interface pilhaOuros
                limparPilhaNaipe(1);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaOuros.TOPO))
                {
                    gotoxy(77, 3);
                    printf("-------");
                    gotoxy(77, 4);
                    printf("|  %c  |", 4);
                    gotoxy(77, 5);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaOuros, 77, 4, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna1, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(1);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaOuros, pilhaColuna2))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaOuros
                tpCarta aux = Pop(pilhaOuros);
                // limpar interface pilhaOuros
                limparPilhaNaipe(1);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaOuros.TOPO))
                {
                    gotoxy(77, 3);
                    printf("-------");
                    gotoxy(77, 4);
                    printf("|  %c  |", 4);
                    gotoxy(77, 5);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaOuros, 77, 4, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna2, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(2);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaOuros, pilhaColuna3))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaOuros
                tpCarta aux = Pop(pilhaOuros);
                // limpar interface pilhaOuros
                limparPilhaNaipe(1);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaOuros.TOPO))
                {
                    gotoxy(77, 3);
                    printf("-------");
                    gotoxy(77, 4);
                    printf("|  %c  |", 4);
                    gotoxy(77, 5);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaOuros, 77, 4, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna3, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(3);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaOuros, pilhaColuna4))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaOuros
                tpCarta aux = Pop(pilhaOuros);
                // limpar interface pilhaOuros
                limparPilhaNaipe(1);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaOuros.TOPO))
                {
                    gotoxy(77, 3);
                    printf("-------");
                    gotoxy(77, 4);
                    printf("|  %c  |", 4);
                    gotoxy(77, 5);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaOuros, 77, 4, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna4, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(4);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaOuros, pilhaColuna5))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaOuros
                tpCarta aux = Pop(pilhaOuros);
                // limpar interface pilhaOuros
                limparPilhaNaipe(1);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaOuros.TOPO))
                {
                    gotoxy(77, 3);
                    printf("-------");
                    gotoxy(77, 4);
                    printf("|  %c  |", 4);
                    gotoxy(77, 5);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaOuros, 77, 4, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna5, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(5);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaOuros, pilhaColuna6))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaOuros
                tpCarta aux = Pop(pilhaOuros);
                // limpar interface pilhaOuros
                limparPilhaNaipe(1);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaOuros.TOPO))
                {
                    gotoxy(77, 3);
                    printf("-------");
                    gotoxy(77, 4);
                    printf("|  %c  |", 4);
                    gotoxy(77, 5);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaOuros, 77, 4, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna6, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(6);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'G':
            // ESCOLHEU MONTE 7
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaOuros, pilhaColuna7))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaOuros
                tpCarta aux = Pop(pilhaOuros);
                // limpar interface pilhaOuros
                limparPilhaNaipe(1);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaOuros.TOPO))
                {
                    gotoxy(77, 3);
                    printf("-------");
                    gotoxy(77, 4);
                    printf("|  %c  |", 4);
                    gotoxy(77, 5);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaOuros, 77, 4, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna7, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(7);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        default:
            break;
        }
        break;
    case 'B':
        // ESCOLHEU MONTE ESPADAS
        limpaMenu();
        gotoxy(1, 18);
        printf("Para: ");
        opMoverPara = submenuMontesColunas();
        switch (opMoverPara)
        {
        case 'A':
            // ESCOLHEU MONTE 1
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaEspadas, pilhaColuna1))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaEspadas
                tpCarta aux = Pop(pilhaEspadas);
                // limpar interface pilhaEspadas
                limparPilhaNaipe(2);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaEspadas.TOPO))
                {
                    gotoxy(77, 6);
                    printf("-------");
                    gotoxy(77, 7);
                    printf("|  %c  |", 6);
                    gotoxy(77, 8);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaEspadas, 77, 7, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna1, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(1);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaEspadas, pilhaColuna2))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaEspadas
                tpCarta aux = Pop(pilhaEspadas);
                // limpar interface pilhaEspadas
                limparPilhaNaipe(2);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaEspadas.TOPO))
                {
                    gotoxy(77, 6);
                    printf("-------");
                    gotoxy(77, 7);
                    printf("|  %c  |", 6);
                    gotoxy(77, 8);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaEspadas, 77, 7, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna2, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(2);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaEspadas, pilhaColuna3))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaEspadas
                tpCarta aux = Pop(pilhaEspadas);
                // limpar interface pilhaEspadas
                limparPilhaNaipe(2);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaEspadas.TOPO))
                {
                    gotoxy(77, 6);
                    printf("-------");
                    gotoxy(77, 7);
                    printf("|  %c  |", 6);
                    gotoxy(77, 8);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaEspadas, 77, 7, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna3, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(3);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaEspadas, pilhaColuna4))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaEspadas
                tpCarta aux = Pop(pilhaEspadas);
                // limpar interface pilhaEspadas
                limparPilhaNaipe(2);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaEspadas.TOPO))
                {
                    gotoxy(77, 6);
                    printf("-------");
                    gotoxy(77, 7);
                    printf("|  %c  |", 6);
                    gotoxy(77, 8);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaEspadas, 77, 7, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna4, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(4);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaEspadas, pilhaColuna5))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaEspadas
                tpCarta aux = Pop(pilhaEspadas);
                // limpar interface pilhaEspadas
                limparPilhaNaipe(2);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaEspadas.TOPO))
                {
                    gotoxy(77, 6);
                    printf("-------");
                    gotoxy(77, 7);
                    printf("|  %c  |", 6);
                    gotoxy(77, 8);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaEspadas, 77, 7, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna5, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(5);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaEspadas, pilhaColuna6))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaEspadas
                tpCarta aux = Pop(pilhaEspadas);
                // limpar interface pilhaEspadas
                limparPilhaNaipe(2);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaEspadas.TOPO))
                {
                    gotoxy(77, 6);
                    printf("-------");
                    gotoxy(77, 7);
                    printf("|  %c  |", 6);
                    gotoxy(77, 8);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaEspadas, 77, 7, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna6, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(6);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'G':
            // ESCOLHEU MONTE 7
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaEspadas, pilhaColuna7))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaEspadas
                tpCarta aux = Pop(pilhaEspadas);
                // limpar interface pilhaEspadas
                limparPilhaNaipe(2);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaEspadas.TOPO))
                {
                    gotoxy(77, 6);
                    printf("-------");
                    gotoxy(77, 7);
                    printf("|  %c  |", 6);
                    gotoxy(77, 8);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaEspadas, 77, 7, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna7, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(7);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        default:
            break;
        }
        break;
    case 'C':
        // ESCOLHEU MONTE COPAS
        limpaMenu();
        gotoxy(1, 18);
        printf("Para: ");
        opMoverPara = submenuMontesColunas();
        switch (opMoverPara)
        {
        case 'A':
            // ESCOLHEU MONTE 1
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaCopas, pilhaColuna1))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaCopas
                tpCarta aux = Pop(pilhaCopas);
                // limpar interface pilhaCopas
                limparPilhaNaipe(3);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaCopas.TOPO))
                {
                    gotoxy(77, 9);
                    printf("-------");
                    gotoxy(77, 10);
                    printf("|  %c  |", 3);
                    gotoxy(77, 11);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaCopas, 77, 10, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna1, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(1);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaCopas, pilhaColuna2))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaCopas
                tpCarta aux = Pop(pilhaCopas);
                // limpar interface pilhaCopas
                limparPilhaNaipe(3);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaCopas.TOPO))
                {
                    gotoxy(77, 9);
                    printf("-------");
                    gotoxy(77, 10);
                    printf("|  %c  |", 3);
                    gotoxy(77, 11);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaCopas, 77, 10, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna2, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(2);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaCopas, pilhaColuna3))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaCopas
                tpCarta aux = Pop(pilhaCopas);
                // limpar interface pilhaCopas
                limparPilhaNaipe(3);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaCopas.TOPO))
                {
                    gotoxy(77, 9);
                    printf("-------");
                    gotoxy(77, 10);
                    printf("|  %c  |", 3);
                    gotoxy(77, 11);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaCopas, 77, 10, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna3, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(3);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaCopas, pilhaColuna4))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaCopas
                tpCarta aux = Pop(pilhaCopas);
                // limpar interface pilhaCopas
                limparPilhaNaipe(3);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaCopas.TOPO))
                {
                    gotoxy(77, 9);
                    printf("-------");
                    gotoxy(77, 10);
                    printf("|  %c  |", 3);
                    gotoxy(77, 11);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaCopas, 77, 10, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna4, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(4);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaCopas, pilhaColuna5))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaCopas
                tpCarta aux = Pop(pilhaCopas);
                // limpar interface pilhaCopas
                limparPilhaNaipe(3);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaCopas.TOPO))
                {
                    gotoxy(77, 9);
                    printf("-------");
                    gotoxy(77, 10);
                    printf("|  %c  |", 3);
                    gotoxy(77, 11);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaCopas, 77, 10, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna5, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(5);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaCopas, pilhaColuna6))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaCopas
                tpCarta aux = Pop(pilhaCopas);
                // limpar interface pilhaCopas
                limparPilhaNaipe(3);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaCopas.TOPO))
                {
                    gotoxy(77, 9);
                    printf("-------");
                    gotoxy(77, 10);
                    printf("|  %c  |", 3);
                    gotoxy(77, 11);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaCopas, 77, 10, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna6, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(6);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'G':
            // ESCOLHEU MONTE 7
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaCopas, pilhaColuna7))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaCopas
                tpCarta aux = Pop(pilhaCopas);
                // limpar interface pilhaCopas
                limparPilhaNaipe(3);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaCopas.TOPO))
                {
                    gotoxy(77, 9);
                    printf("-------");
                    gotoxy(77, 10);
                    printf("|  %c  |", 3);
                    gotoxy(77, 11);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaCopas, 77, 10, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna7, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(7);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        default:
            break;
        }
        break;
    case 'D':
        // ESCOLHEU MONTE PAUS
        limpaMenu();
        gotoxy(1, 18);
        printf("Para: ");
        opMoverPara = submenuMontesColunas();
        switch (opMoverPara)
        {
        case 'A':
            // ESCOLHEU MONTE 1
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaPaus, pilhaColuna1))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaPaus
                tpCarta aux = Pop(pilhaPaus);
                // limpar interface pilhaPaus
                limparPilhaNaipe(4);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaPaus.TOPO))
                {
                    gotoxy(77, 12);
                    printf("-------");
                    gotoxy(77, 13);
                    printf("|  %c  |", 5);
                    gotoxy(77, 14);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaPaus, 77, 13, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna1, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(1);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaPaus, pilhaColuna2))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaPaus
                tpCarta aux = Pop(pilhaPaus);
                // limpar interface pilhaPaus
                limparPilhaNaipe(4);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaPaus.TOPO))
                {
                    gotoxy(77, 12);
                    printf("-------");
                    gotoxy(77, 13);
                    printf("|  %c  |", 5);
                    gotoxy(77, 14);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaPaus, 77, 13, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna2, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(2);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaPaus, pilhaColuna3))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaPaus
                tpCarta aux = Pop(pilhaPaus);
                // limpar interface pilhaPaus
                limparPilhaNaipe(4);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaPaus.TOPO))
                {
                    gotoxy(77, 12);
                    printf("-------");
                    gotoxy(77, 13);
                    printf("|  %c  |", 5);
                    gotoxy(77, 14);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaPaus, 77, 13, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna3, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(3);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaPaus, pilhaColuna4))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaPaus
                tpCarta aux = Pop(pilhaPaus);
                // limpar interface pilhaPaus
                limparPilhaNaipe(4);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaPaus.TOPO))
                {
                    gotoxy(77, 12);
                    printf("-------");
                    gotoxy(77, 13);
                    printf("|  %c  |", 5);
                    gotoxy(77, 14);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaPaus, 77, 13, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna4, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(4);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaPaus, pilhaColuna5))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaPaus
                tpCarta aux = Pop(pilhaPaus);
                // limpar interface pilhaPaus
                limparPilhaNaipe(4);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaPaus.TOPO))
                {
                    gotoxy(77, 12);
                    printf("-------");
                    gotoxy(77, 13);
                    printf("|  %c  |", 5);
                    gotoxy(77, 14);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaPaus, 77, 13, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna5, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(5);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaPaus, pilhaColuna6))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaPaus
                tpCarta aux = Pop(pilhaPaus);
                // limpar interface pilhaPaus
                limparPilhaNaipe(4);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaPaus.TOPO))
                {
                    gotoxy(77, 12);
                    printf("-------");
                    gotoxy(77, 13);
                    printf("|  %c  |", 5);
                    gotoxy(77, 14);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaPaus, 77, 13, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna6, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(6);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        case 'G':
            // ESCOLHEU MONTE 7
            if (verificaPodeEfeturarjogadaMoveNaipeMesa(pilhaPaus, pilhaColuna7))
            {
                // PODE FAZER JOGADA

                // retirar ultima carta pilhaPaus
                tpCarta aux = Pop(pilhaPaus);
                // limpar interface pilhaPaus
                limparPilhaNaipe(4);
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial, linha 4
                if (Vazia(pilhaPaus.TOPO))
                {
                    gotoxy(77, 12);
                    printf("-------");
                    gotoxy(77, 13);
                    printf("|  %c  |", 5);
                    gotoxy(77, 14);
                    printf("-------");
                }
                else
                {
                    ExbibirTemporarioSoVerPilha(pilhaPaus, 77, 13, 3);
                }
                // adicionar carta na pilhaColuna1
                Push(pilhaColuna7, aux);
                // limpar interface pilhaColuna1
                limparPilhaColuna(7);
                // redesenhar pilhaColuna1
                ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                // chamar adicionar movimento
                contagemDeMovimentos();
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

int verificaJogadaMesaMesa(TpPilha origem, TpPilha destinho, int qteCartasOrigem)
{
    int posPrimeiraCartaOrigem, posUltimaCartaDestino, cont = 0;
    tpCarta aux, aux1;
    while (!Vazia(origem.TOPO) && cont != qteCartasOrigem)
    {
        aux = Pop(origem);
        cont++;
    }
    posPrimeiraCartaOrigem = buscaFigura(aux.figura);
    if (Vazia(destinho.TOPO))
    {
        return posPrimeiraCartaOrigem != 12 ? 0 : 1;
    }
    else
    {
        aux1 = ElementoTopo(destinho);
        if (aux.preto == aux1.preto)
            return 0;
        posUltimaCartaDestino = buscaFigura(aux1.figura);
        if (posPrimeiraCartaOrigem != posUltimaCartaDestino - 1)
        {
            return 0;
        }
    }
    return 1;
}

int indexPrimeiraCartaViradaPraCima(TpPilha p)
{
    int cont = 0;
    tpCarta ant, atual;
    while (!Vazia(p.TOPO))
    {
        atual = Pop(p);
        if (atual.viradaPraCima == 1)
        {
            ant = atual;
        }
        else
        {
            return cont;
        }
        cont++;
    }
}

void moveMesaMesa(TpPilha &pilhaColuna1, TpPilha &pilhaColuna2, TpPilha &pilhaColuna3, TpPilha &pilhaColuna4, TpPilha &pilhaColuna5, TpPilha &pilhaColuna6, TpPilha &pilhaColuna7)
{
    limpaMenu();
    gotoxy(1, 18);
    printf("Pegar de: ");
    int pos;
    char op = submenuMontesColunas();
    limpaMenu();
    switch (op)
    {
    case 'A':
        // ESCOLHEU pilhaColuna1
        if (Vazia(pilhaColuna1.TOPO))
        {
            gotoxy(1, 18);
            printf("Jogada invalida, monte vazio!\nDigite algo para sair...");
            getch();
        }
        else
        {
            gotoxy(1, 18);
            printf("Deseja mover a partir de qual posicao para baixo?: ");
            int qtasCartas = quantasCartasTemNaPilha(pilhaColuna1);
            int indexPrimeiraCartaPraCima = indexPrimeiraCartaViradaPraCima(pilhaColuna1);
            int y = 19 + qtasCartas - 1;
            int i = 0;
            int qteCartasAux = qtasCartas;
            while (i < indexPrimeiraCartaPraCima)
            {
                gotoxy(1, y);
                printf("[%d]", qteCartasAux);
                y--;
                i++;
                qteCartasAux--;
            }
            ExbibirTemporarioSoVerPilha(pilhaColuna1, 5, 19, 1);
            gotoxy(52, 18);
            scanf("%d", &pos);
            if (pos <= qtasCartas - indexPrimeiraCartaPraCima || pos > qtasCartas)
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
                limpaMenu();
            }
            else
            {
                int qteDeCartasAMover = qtasCartas - pos + 1;
                limpaMenu();
                gotoxy(1, 18);
                printf("Colocar onde: ");
                op = submenuMontesColunas(1);
                switch (op)
                {
                case 'B':
                    if (!verificaJogadaMesaMesa(pilhaColuna1, pilhaColuna2, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna1));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna2, Pop(aux));
                        }
                        limparPilhaColuna(2);
                        limparPilhaColuna(1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'C':
                    if (!verificaJogadaMesaMesa(pilhaColuna1, pilhaColuna3, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna1));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna3, Pop(aux));
                        }
                        limparPilhaColuna(3);
                        limparPilhaColuna(1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'D':
                    if (!verificaJogadaMesaMesa(pilhaColuna1, pilhaColuna4, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna1));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna4, Pop(aux));
                        }
                        limparPilhaColuna(4);
                        limparPilhaColuna(1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'E':
                    if (!verificaJogadaMesaMesa(pilhaColuna1, pilhaColuna5, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna1));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna5, Pop(aux));
                        }
                        limparPilhaColuna(5);
                        limparPilhaColuna(1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'F':
                    if (!verificaJogadaMesaMesa(pilhaColuna1, pilhaColuna6, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna1));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna6, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'G':
                    if (!verificaJogadaMesaMesa(pilhaColuna1, pilhaColuna7, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna1));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna7, Pop(aux));
                        }
                        limparPilhaColuna(7);
                        limparPilhaColuna(1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                default:
                    break;
                }
            }
            // getch();
        }
        break;
    case 'B':
        // ESCOLHEU pilhaColuna2
        if (Vazia(pilhaColuna2.TOPO))
        {
            gotoxy(1, 18);
            printf("Jogada invalida, monte vazio!\nDigite algo para sair...");
            getch();
        }
        else
        {
            gotoxy(1, 18);
            printf("Deseja mover a partir de qual posicao para baixo?: ");
            int qtasCartas = quantasCartasTemNaPilha(pilhaColuna2);
            int indexPrimeiraCartaPraCima = indexPrimeiraCartaViradaPraCima(pilhaColuna2);
            int y = 19 + qtasCartas - 1;
            int i = 0;
            int qteCartasAux = qtasCartas;
            while (i < indexPrimeiraCartaPraCima)
            {
                gotoxy(1, y);
                printf("[%d]", qteCartasAux);
                y--;
                i++;
                qteCartasAux--;
            }
            ExbibirTemporarioSoVerPilha(pilhaColuna2, 5, 19, 1);
            gotoxy(52, 18);
            scanf("%d", &pos);
            if (pos <= qtasCartas - indexPrimeiraCartaPraCima || pos > qtasCartas)
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
                limpaMenu();
            }
            else
            {
                int qteDeCartasAMover = qtasCartas - pos + 1;
                limpaMenu();
                gotoxy(1, 18);
                printf("Colocar onde: ");
                op = submenuMontesColunas(7);
                switch (op)
                {
                case 'A':
                    if (!verificaJogadaMesaMesa(pilhaColuna2, pilhaColuna1, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna2));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna1, Pop(aux));
                        }
                        limparPilhaColuna(1);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'C':
                    if (!verificaJogadaMesaMesa(pilhaColuna2, pilhaColuna3, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna2));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna3, Pop(aux));
                        }
                        limparPilhaColuna(3);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'D':
                    if (!verificaJogadaMesaMesa(pilhaColuna2, pilhaColuna4, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna2));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna4, Pop(aux));
                        }
                        limparPilhaColuna(4);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'E':
                    if (!verificaJogadaMesaMesa(pilhaColuna2, pilhaColuna5, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna2));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna5, Pop(aux));
                        }
                        limparPilhaColuna(5);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'F':
                    if (!verificaJogadaMesaMesa(pilhaColuna2, pilhaColuna6, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna2));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna6, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'G':
                    if (!verificaJogadaMesaMesa(pilhaColuna2, pilhaColuna7, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna2));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna7, Pop(aux));
                        }
                        limparPilhaColuna(7);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                default:
                    break;
                }
            }
            // getch();
        }
        break;
    case 'C':
        // ESCOLHEU pilhaColuna3

        if (Vazia(pilhaColuna3.TOPO))
        {
            gotoxy(1, 18);
            printf("Jogada invalida, monte vazio!\nDigite algo para sair...");
            getch();
        }
        else
        {
            gotoxy(1, 18);
            printf("Deseja mover a partir de qual posicao para baixo?: ");
            int qtasCartas = quantasCartasTemNaPilha(pilhaColuna3);
            int indexPrimeiraCartaPraCima = indexPrimeiraCartaViradaPraCima(pilhaColuna3);
            int y = 19 + qtasCartas - 1;
            int i = 0;
            int qteCartasAux = qtasCartas;
            while (i < indexPrimeiraCartaPraCima)
            {
                gotoxy(1, y);
                printf("[%d]", qteCartasAux);
                y--;
                i++;
                qteCartasAux--;
            }
            ExbibirTemporarioSoVerPilha(pilhaColuna3, 5, 19, 1);
            gotoxy(52, 18);
            scanf("%d", &pos);
            if (pos <= qtasCartas - indexPrimeiraCartaPraCima || pos > qtasCartas)
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
                limpaMenu();
            }
            else
            {
                int qteDeCartasAMover = qtasCartas - pos + 1;
                limpaMenu();
                gotoxy(1, 18);
                printf("Colocar onde: ");
                op = submenuMontesColunas(7);
                switch (op)
                {
                case 'A':
                    if (!verificaJogadaMesaMesa(pilhaColuna3, pilhaColuna1, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna3));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna1, Pop(aux));
                        }
                        limparPilhaColuna(1);
                        limparPilhaColuna(3);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'B':
                    if (!verificaJogadaMesaMesa(pilhaColuna3, pilhaColuna2, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna3));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna2, Pop(aux));
                        }
                        limparPilhaColuna(3);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'D':
                    if (!verificaJogadaMesaMesa(pilhaColuna3, pilhaColuna4, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna3));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna4, Pop(aux));
                        }
                        limparPilhaColuna(4);
                        limparPilhaColuna(3);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'E':
                    if (!verificaJogadaMesaMesa(pilhaColuna3, pilhaColuna5, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna3));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna5, Pop(aux));
                        }
                        limparPilhaColuna(5);
                        limparPilhaColuna(3);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'F':
                    if (!verificaJogadaMesaMesa(pilhaColuna3, pilhaColuna6, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna3));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna6, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(3);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'G':
                    if (!verificaJogadaMesaMesa(pilhaColuna3, pilhaColuna7, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna3));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna7, Pop(aux));
                        }
                        limparPilhaColuna(7);
                        limparPilhaColuna(3);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                default:
                    break;
                }
            }
            // getch();
        }
        break;
    case 'D':
        // ESCOLHEU pilhaColuna4

        if (Vazia(pilhaColuna4.TOPO))
        {
            gotoxy(1, 18);
            printf("Jogada invalida, monte vazio!\nDigite algo para sair...");
            getch();
        }
        else
        {
            gotoxy(1, 18);
            printf("Deseja mover a partir de qual posicao para baixo?: ");
            int qtasCartas = quantasCartasTemNaPilha(pilhaColuna4);
            int indexPrimeiraCartaPraCima = indexPrimeiraCartaViradaPraCima(pilhaColuna4);
            int y = 19 + qtasCartas - 1;
            int i = 0;
            int qteCartasAux = qtasCartas;
            while (i < indexPrimeiraCartaPraCima)
            {
                gotoxy(1, y);
                printf("[%d]", qteCartasAux);
                y--;
                i++;
                qteCartasAux--;
            }
            ExbibirTemporarioSoVerPilha(pilhaColuna4, 5, 19, 1);
            gotoxy(52, 18);
            scanf("%d", &pos);
            if (pos <= qtasCartas - indexPrimeiraCartaPraCima || pos > qtasCartas)
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
                limpaMenu();
            }
            else
            {
                int qteDeCartasAMover = qtasCartas - pos + 1;
                limpaMenu();
                gotoxy(1, 18);
                printf("Colocar onde: ");
                op = submenuMontesColunas(7);
                switch (op)
                {
                case 'A':
                    if (!verificaJogadaMesaMesa(pilhaColuna4, pilhaColuna1, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna4));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna1, Pop(aux));
                        }
                        limparPilhaColuna(1);
                        limparPilhaColuna(4);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'B':
                    if (!verificaJogadaMesaMesa(pilhaColuna4, pilhaColuna2, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna4));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna2, Pop(aux));
                        }
                        limparPilhaColuna(4);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'C':
                    if (!verificaJogadaMesaMesa(pilhaColuna4, pilhaColuna3, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna4));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna3, Pop(aux));
                        }
                        limparPilhaColuna(3);
                        limparPilhaColuna(4);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'E':
                    if (!verificaJogadaMesaMesa(pilhaColuna4, pilhaColuna5, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna4));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna5, Pop(aux));
                        }
                        limparPilhaColuna(5);
                        limparPilhaColuna(4);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'F':
                    if (!verificaJogadaMesaMesa(pilhaColuna4, pilhaColuna6, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna4));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna6, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(4);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'G':
                    if (!verificaJogadaMesaMesa(pilhaColuna4, pilhaColuna7, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna4));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna7, Pop(aux));
                        }
                        limparPilhaColuna(7);
                        limparPilhaColuna(4);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                default:
                    break;
                }
            }
            // getch();
        }
        break;
    case 'E':
        // ESCOLHEU pilhaColuna5

        if (Vazia(pilhaColuna5.TOPO))
        {
            gotoxy(1, 18);
            printf("Jogada invalida, monte vazio!\nDigite algo para sair...");
            getch();
        }
        else
        {
            gotoxy(1, 18);
            printf("Deseja mover a partir de qual posicao para baixo?: ");
            int qtasCartas = quantasCartasTemNaPilha(pilhaColuna5);
            int indexPrimeiraCartaPraCima = indexPrimeiraCartaViradaPraCima(pilhaColuna5);
            int y = 19 + qtasCartas - 1;
            int i = 0;
            int qteCartasAux = qtasCartas;
            while (i < indexPrimeiraCartaPraCima)
            {
                gotoxy(1, y);
                printf("[%d]", qteCartasAux);
                y--;
                i++;
                qteCartasAux--;
            }
            ExbibirTemporarioSoVerPilha(pilhaColuna5, 5, 19, 1);
            gotoxy(52, 18);
            scanf("%d", &pos);
            if (pos <= qtasCartas - indexPrimeiraCartaPraCima || pos > qtasCartas)
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
                limpaMenu();
            }
            else
            {
                int qteDeCartasAMover = qtasCartas - pos + 1;
                limpaMenu();
                gotoxy(1, 18);
                printf("Colocar onde: ");
                op = submenuMontesColunas(7);
                switch (op)
                {
                case 'A':
                    if (!verificaJogadaMesaMesa(pilhaColuna5, pilhaColuna1, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna5));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna1, Pop(aux));
                        }
                        limparPilhaColuna(1);
                        limparPilhaColuna(5);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'B':
                    if (!verificaJogadaMesaMesa(pilhaColuna5, pilhaColuna2, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna5));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna2, Pop(aux));
                        }
                        limparPilhaColuna(5);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'C':
                    if (!verificaJogadaMesaMesa(pilhaColuna5, pilhaColuna3, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna5));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna3, Pop(aux));
                        }
                        limparPilhaColuna(3);
                        limparPilhaColuna(5);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'D':
                    if (!verificaJogadaMesaMesa(pilhaColuna5, pilhaColuna4, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna5));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna4, Pop(aux));
                        }
                        limparPilhaColuna(5);
                        limparPilhaColuna(4);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'F':
                    if (!verificaJogadaMesaMesa(pilhaColuna5, pilhaColuna6, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna5));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna6, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(5);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'G':
                    if (!verificaJogadaMesaMesa(pilhaColuna5, pilhaColuna7, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna5));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna7, Pop(aux));
                        }
                        limparPilhaColuna(7);
                        limparPilhaColuna(5);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                default:
                    break;
                }
            }
            // getch();
        }
        break;
    case 'F':
        // ESCOLHEU pilhaColuna6
        if (Vazia(pilhaColuna6.TOPO))
        {
            gotoxy(1, 18);
            printf("Jogada invalida, monte vazio!\nDigite algo para sair...");
            getch();
        }
        else
        {
            gotoxy(1, 18);
            printf("Deseja mover a partir de qual posicao para baixo?: ");
            int qtasCartas = quantasCartasTemNaPilha(pilhaColuna6);
            int indexPrimeiraCartaPraCima = indexPrimeiraCartaViradaPraCima(pilhaColuna6);
            int y = 19 + qtasCartas - 1;
            int i = 0;
            int qteCartasAux = qtasCartas;
            while (i < indexPrimeiraCartaPraCima)
            {
                gotoxy(1, y);
                printf("[%d]", qteCartasAux);
                y--;
                i++;
                qteCartasAux--;
            }
            ExbibirTemporarioSoVerPilha(pilhaColuna6, 5, 19, 1);
            gotoxy(52, 18);
            scanf("%d", &pos);
            if (pos <= qtasCartas - indexPrimeiraCartaPraCima || pos > qtasCartas)
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
                limpaMenu();
            }
            else
            {
                int qteDeCartasAMover = qtasCartas - pos + 1;
                limpaMenu();
                gotoxy(1, 18);
                printf("Colocar onde: ");
                op = submenuMontesColunas(7);
                switch (op)
                {
                case 'A':
                    if (!verificaJogadaMesaMesa(pilhaColuna6, pilhaColuna1, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna6));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna1, Pop(aux));
                        }
                        limparPilhaColuna(1);
                        limparPilhaColuna(6);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 58, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'B':
                    if (!verificaJogadaMesaMesa(pilhaColuna6, pilhaColuna2, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna6));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna2, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(2);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 58, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'C':
                    if (!verificaJogadaMesaMesa(pilhaColuna6, pilhaColuna3, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna6));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna3, Pop(aux));
                        }
                        limparPilhaColuna(3);
                        limparPilhaColuna(6);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 58, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'D':
                    if (!verificaJogadaMesaMesa(pilhaColuna6, pilhaColuna4, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna6));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna4, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(4);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 58, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'E':
                    if (!verificaJogadaMesaMesa(pilhaColuna6, pilhaColuna5, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna6));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna5, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(5);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'G':
                    if (!verificaJogadaMesaMesa(pilhaColuna5, pilhaColuna7, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna5));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna7, Pop(aux));
                        }
                        limparPilhaColuna(7);
                        limparPilhaColuna(5);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                default:
                    break;
                }
            }
            // getch();
        }
        break;
    case 'G':
        // ESCOLHEU pilhaColuna7

        if (Vazia(pilhaColuna7.TOPO))
        {
            gotoxy(1, 18);
            printf("Jogada invalida, monte vazio!\nDigite algo para sair...");
            getch();
        }
        else
        {
            gotoxy(1, 18);
            printf("Deseja mover a partir de qual posicao para baixo?: ");
            int qtasCartas = quantasCartasTemNaPilha(pilhaColuna7);
            int indexPrimeiraCartaPraCima = indexPrimeiraCartaViradaPraCima(pilhaColuna7);
            int y = 19 + qtasCartas - 1;
            int i = 0;
            int qteCartasAux = qtasCartas;
            while (i < indexPrimeiraCartaPraCima)
            {
                gotoxy(1, y);
                printf("[%d]", qteCartasAux);
                y--;
                i++;
                qteCartasAux--;
            }
            ExbibirTemporarioSoVerPilha(pilhaColuna7, 5, 19, 1);
            gotoxy(52, 18);
            scanf("%d", &pos);
            if (pos <= qtasCartas - indexPrimeiraCartaPraCima || pos > qtasCartas)
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida\nDigite algo para voltar...");
                getch();
                limpaMenu();
            }
            else
            {
                int qteDeCartasAMover = qtasCartas - pos + 1;
                limpaMenu();
                gotoxy(1, 18);
                printf("Colocar onde: ");
                op = submenuMontesColunas(7);
                switch (op)
                {
                case 'A':
                    if (!verificaJogadaMesaMesa(pilhaColuna7, pilhaColuna1, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna7));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna1, Pop(aux));
                        }
                        limparPilhaColuna(1);
                        limparPilhaColuna(7);
                        ExbibirTemporarioSoVerPilha(pilhaColuna1, 14, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'B':
                    if (!verificaJogadaMesaMesa(pilhaColuna7, pilhaColuna2, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna7));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna2, Pop(aux));
                        }
                        limparPilhaColuna(2);
                        limparPilhaColuna(7);
                        ExbibirTemporarioSoVerPilha(pilhaColuna2, 23, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'C':
                    if (!verificaJogadaMesaMesa(pilhaColuna7, pilhaColuna3, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna7));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna3, Pop(aux));
                        }
                        limparPilhaColuna(3);
                        limparPilhaColuna(7);
                        ExbibirTemporarioSoVerPilha(pilhaColuna3, 32, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'D':
                    if (!verificaJogadaMesaMesa(pilhaColuna7, pilhaColuna4, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna7));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna4, Pop(aux));
                        }
                        limparPilhaColuna(4);
                        limparPilhaColuna(7);
                        ExbibirTemporarioSoVerPilha(pilhaColuna4, 41, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'E':
                    if (!verificaJogadaMesaMesa(pilhaColuna7, pilhaColuna5, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna7));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna5, Pop(aux));
                        }
                        limparPilhaColuna(5);
                        limparPilhaColuna(7);
                        ExbibirTemporarioSoVerPilha(pilhaColuna5, 50, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                case 'F':
                    if (!verificaJogadaMesaMesa(pilhaColuna7, pilhaColuna6, qteDeCartasAMover))
                    {
                        limpaMenu();
                        gotoxy(1, 18);
                        printf("Jogada invalida\nDigite algo para voltar...");
                        getch();
                    }
                    else
                    {
                        TpPilha aux;
                        Inicializar(aux);
                        int cont = 0;
                        while (cont != qteDeCartasAMover)
                            Push(aux, Pop(pilhaColuna7));
                        while (!Vazia(aux.TOPO))
                        {
                            Push(pilhaColuna6, Pop(aux));
                        }
                        limparPilhaColuna(6);
                        limparPilhaColuna(7);
                        ExbibirTemporarioSoVerPilha(pilhaColuna6, 59, 3, 1);
                        ExbibirTemporarioSoVerPilha(pilhaColuna7, 68, 3, 1);
                        limpaMenu();
                        contagemDeMovimentos();
                    }
                    break;
                default:
                    break;
                }
            }
            // getch();
        }
        break;
    default:
        break;
    }
}

void moveMonteViradoParaMesa()
{
}

void moveMonteViradoParaNaipe()
{
}

void limparPilhaMonteVirado()
{
    int colI = 2, linI = 10, linF = 15, colF = 9;
    textcolor(15);
    textbackground(0);
    for (int i = linI; i < linF; i++)
    {
        for (int j = 0; j < colF; j++)
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
}

int quantasCartasTemNaPilha(TpPilha p)
{
    int cont = 0;
    while (!Vazia(p.TOPO))
    {
        Pop(p);
        cont++;
    }
    return cont;
}

void pegarCartaOuResetarBaralho(TpPilha &pilhaMonte, TpPilha &pilhaMonteVirado, int &qteCartasPilhaMonte)
{
    // verificar se pilhaMonte está vazia e se pilhaMonteVirado tbm
    // gotoxy();
    if (Vazia(pilhaMonte.TOPO) && Vazia(pilhaMonteVirado.TOPO))
    {
        gotoxy(1, 16);
        printf("Não há mais cartas para pegar!");
    }
    else if (Vazia(pilhaMonte.TOPO) && !Vazia(pilhaMonteVirado.TOPO))
    {
        limparPilhaMonteVirado();
        // jogar as cartas do monte virado pro monte normal e puxar uma carta

        int qtasCartas = quantasCartasTemNaPilha(pilhaMonteVirado);
        TpPilha aux;
        Inicializar(aux);
        while (!Vazia(pilhaMonteVirado.TOPO))
        {
            Push(pilhaMonte, Pop(pilhaMonteVirado));
        }
        // while (!Vazia(aux.TOPO))
        // {
        //     Push(pilhaMonte, Pop(aux));
        // }

        // tpCarta aux[qtasCartas];
        // for (int i = 0; i < qtasCartas; i++)
        //     aux[i] = Pop(pilhaMonteVirado);

        // srand(time(NULL));
        // embaralhar(aux, qtasCartas);

        // for (int j = 0; j < qtasCartas; j++)
        // {
        //     Push(pilhaMonte, aux[j]);
        // }
        qteCartasPilhaMonte = qtasCartas;
        // tirar carta do pilhaMonte
        // colocar no pilhaMonteViredo
        Push(pilhaMonteVirado, Pop(pilhaMonte));
        // diminuir contador de cartas no monte
        qteCartasPilhaMonte--;
        int aux2 = qteCartasPilhaMonte % 10;
        textcolor(0);
        textbackground(15);
        gotoxy(6, 8);
        printf("%d", qteCartasPilhaMonte / 10);
        gotoxy(7, 8);
        printf("%d", aux2);
        gotoxy(70, 24);
        textcolor(15);
        textbackground(0);
        // dar clear visual na pilhaMonteVirado
        // limparPilhaMonteVirado();
        // exibir pilhaMonteVirado
        ExbibirTemporarioSoVerPilha(pilhaMonteVirado, 2, 10, 2);
    }
    else
    {
        // PUXAR UMA CARTA

        // tirar carta do pilhaMonte
        // colocar no pilhaMonteViredo
        Push(pilhaMonteVirado, Pop(pilhaMonte));
        // diminuir contador de cartas no monte
        qteCartasPilhaMonte--;
        int aux = qteCartasPilhaMonte % 10;
        textcolor(0);
        textbackground(15);
        gotoxy(6, 8);
        printf("%d", qteCartasPilhaMonte / 10);
        gotoxy(7, 8);
        printf("%d", aux);
        gotoxy(70, 24);
        textcolor(15);
        textbackground(0);
        // dar clear visual na pilhaMonteVirado
        limparPilhaMonteVirado();
        // exibir pilhaMonteVirado
        ExbibirTemporarioSoVerPilha(pilhaMonteVirado, 2, 10, 2);
    }
}

void executar()
{
    // fazer sistema de pontuação?
    // pode desfazer jogada? ideia legal
    int qteCartasPilhaMonte;
    TpPilha pilhaMonte, pilhaMonteVirado, pilhaOuros, pilhaEspadas, pilhaCopas, pilhaPaus, pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7;
    Inicializar(pilhaMonte);
    Inicializar(pilhaMonteVirado);
    Inicializar(pilhaOuros);
    Inicializar(pilhaEspadas);
    Inicializar(pilhaCopas);
    Inicializar(pilhaPaus);
    Inicializar(pilhaColuna1);
    Inicializar(pilhaColuna2);
    Inicializar(pilhaColuna3);
    Inicializar(pilhaColuna4);
    Inicializar(pilhaColuna5);
    Inicializar(pilhaColuna6);
    Inicializar(pilhaColuna7);
    inicializarMesa(pilhaMonte, pilhaMonteVirado, pilhaOuros, pilhaEspadas, pilhaCopas, pilhaPaus, pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7, qteCartasPilhaMonte);
    char op;
    do
    {
        op = menuPrincipal(pilhaMonte, pilhaMonteVirado);
        switch (op)
        {
        case 'A':
            pegarCartaOuResetarBaralho(pilhaMonte, pilhaMonteVirado, qteCartasPilhaMonte);
            limpaMenu();
            break;
        case 'B':
            moveMesaNaipe();
            // contagemDeMovimentos();
            break;
        case 'C':
            moveNaipeMesa(pilhaOuros, pilhaEspadas, pilhaCopas, pilhaPaus, pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7);
            limpaMenu();
            // contagemDeMovimentos();
            break;
        case 'D':
            moveMesaMesa(pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7);
            limpaMenu();
            // contagemDeMovimentos();
            break;
        case 'E':
            moveMonteViradoParaMesa();
            // contagemDeMovimentos();
            break;
        case 'F':
            moveMonteViradoParaNaipe(pilhaMonteVirado, pilhaOuros, pilhaEspadas, pilhaCopas, pilhaPaus);
            limpaMenu();
            // contagemDeMovimentos();
            break;
        default:
            break;
        }
    } while (op != 27 && !verificaGanhou(pilhaOuros, pilhaEspadas, pilhaCopas, pilhaPaus));
}

void limpaMenu()
{
    // printar espacos pra limpar menu
    for (int i = 16; i <= 30; i++)
    {
        for (int j = 1; j < 80; j++)
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
}

int verificaGanhou(TpPilha pilhaOuros, TpPilha pilhaEspadas, TpPilha pilhaCopas, TpPilha pilhaPaus)
{
    // verificar se os 4 montes dos naipes estão cheios
    if (quantasCartasTemNaPilha(pilhaOuros) == 13 && quantasCartasTemNaPilha(pilhaEspadas) == 13 && quantasCartasTemNaPilha(pilhaCopas) == 13 && quantasCartasTemNaPilha(pilhaPaus) == 13)
    {
        return 1;
    }
    return 0;
}

int buscaFigura(char figBuscada[3])
{
    char fig[13][3] = {"A",
                       "2",
                       "3",
                       "4",
                       "5",
                       "6",
                       "7",
                       "8",
                       "9",
                       "10",
                       "J",
                       "Q",
                       "K"};
    for (int i = 0; i < 13; i++)
    {
        if (strcmp(fig[i], figBuscada) == 0)
        {
            return i;
        }
    };
    return -1;
}

int verificaPodeEfeturarjogadaMoveNaipeMesa(TpPilha monteNaipe, TpPilha monteMesa)
{
    // verificar se carta do monte naipe pode entrar no monte mesa designado
    if (Vazia(monteNaipe.TOPO))
    {
        return 0;
    }
    // char figuras[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    tpCarta cartaTopoMonteNaipe = Pop(monteNaipe);
    int posBuscaCartaTopoMonteNaipe = buscaFigura(cartaTopoMonteNaipe.figura);
    if (Vazia(monteMesa.TOPO))
    {
        if (posBuscaCartaTopoMonteNaipe == 12)
            return true;
        else
            return false;
    }
    else
    {
        tpCarta cartaTopoMonteMesa = Pop(monteMesa);
        if (posBuscaCartaTopoMonteNaipe + 1 == buscaFigura(cartaTopoMonteMesa.figura) ||
            cartaTopoMonteNaipe.preto == cartaTopoMonteMesa.preto)
        {
            return 0;
        }
        return 1;
    }
}

void contagemDeMovimentos()
{
    movimentos++;
    gotoxy(1, 20);
    printf("Movimentos: %d", movimentos);
}

int main()
{
    executar();
    return 0;
}

// a fazeres para agora

// void moveMesaNaipe()

// void moveNaipeMesa()

// void moveMesaMesa()

// void moveMonteViradoParaMesa()

// void moveMonteViradoParaNaipe()
