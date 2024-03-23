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
int buscaFigura(char fig[13][3], char figBuscada[3]);
void popularPilhasColunas(TpPilha &monte, TpPilha &p1, TpPilha &p2, TpPilha &p3, TpPilha &p4, TpPilha &p5, TpPilha &p6, TpPilha &p7);

// mover cartas
void destribuirMesa();
void moveMesaTemp();
void moveNaipeMesa(TpPilha &pilhaOuros, TpPilha &pilhaEspadas, TpPilha &pilhaCopas, TpPilha &pilhaPaus, TpPilha &pilhaColuna1, TpPilha &pilhaColuna2, TpPilha &pilhaColuna3, TpPilha &pilhaColuna4, TpPilha &pilhaColuna5, TpPilha &pilhaColuna6, TpPilha &pilhaColuna7);
void moveMonteViradoParaNaipe(TpPilha monteVirado,TpPilha &pilhaOuros, TpPilha &pilhaEspadas, TpPilha &pilhaCopas, TpPilha &pilhaPaus);
void moveTempMesa();
void moveMesaNaipe();
void moveMonteViradoParaMesa();

// verificacoes
int quantasCartasTemNaPilha(TpPilha p);
void pegarCartaOuResetarBaralho(TpPilha &pilhaMonte, TpPilha &pilhaMonteVirado, int &qteCartasPilhaMonte);
int verificaPodeEfeturarjogadaMoveNaipeMesa(TpPilha monteNaipe, TpPilha monteMesa);
int verificaGanhou(TpPilha pilhaOuros, TpPilha pilhaEspadas, TpPilha pilhaCopas, TpPilha pilhaPaus);
int verificarMoverMonteParaNaipe(TpPilha monteVirado,TpPilha pilhaOuro,TpPilha pilhaEspadas,TpPilha pilhaCopas,TpPilha pilhaPaus,int monte);

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
    Push(p1, Pop(monte));
    Push(p2, Pop(monte));
    Push(p2, Pop(monte));
    Push(p3, Pop(monte));
    Push(p3, Pop(monte));
    Push(p3, Pop(monte));
    Push(p4, Pop(monte));
    Push(p4, Pop(monte));
    Push(p4, Pop(monte));
    Push(p4, Pop(monte));
    Push(p5, Pop(monte));
    Push(p5, Pop(monte));
    Push(p5, Pop(monte));
    Push(p5, Pop(monte));
    Push(p5, Pop(monte));
    Push(p6, Pop(monte));
    Push(p6, Pop(monte));
    Push(p6, Pop(monte));
    Push(p6, Pop(monte));
    Push(p6, Pop(monte));
    Push(p6, Pop(monte));
    Push(p7, Pop(monte));
    Push(p7, Pop(monte));
    Push(p7, Pop(monte));
    Push(p7, Pop(monte));
    Push(p7, Pop(monte));
    Push(p7, Pop(monte));
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
    ExbibirTemporarioSoVerPilha(p1, 14, 3, 0);
    gotoxy(23, 2);
    printf("M - 2");
    ExbibirTemporarioSoVerPilha(p2, 23, 3, 0);
    gotoxy(32, 2);
    printf("M - 3");
    ExbibirTemporarioSoVerPilha(p3, 32, 3, 0);
    gotoxy(41, 2);
    printf("M - 4");
    ExbibirTemporarioSoVerPilha(p4, 41, 3, 0);
    gotoxy(50, 2);
    printf("M - 5");
    ExbibirTemporarioSoVerPilha(p5, 50, 3, 0);
    gotoxy(59, 2);
    printf("M - 6");
    ExbibirTemporarioSoVerPilha(p6, 59, 3, 0);
    gotoxy(68, 2);
    printf("M - 7");
    ExbibirTemporarioSoVerPilha(p7, 68, 3, 0);

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
    printf("Opção desejada: ");
    return toupper(getche());
}

char submenuMontesColunas()
{
    gotoxy(1, 19);
    printf("[A] Monte 1\n");
    printf("[B] Monte 2\n");
    printf("[C] Monte 3\n");
    printf("[D] Monte 4\n");
    printf("[E] Monte 5\n");
    printf("[F] Monte 6\n");
    printf("[G] Monte 7\n");
    printf("Opção desejada: ");
    return toupper(getche());
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

                // limpar interface pilhaOuros
                // redesenhar ultimo elementos da pilha ouros, se vazia fazer o desenho inicial
                // adicionar carta na pilhaColuna1
                // limpar interface pilhaColuna1
                // redesenhar pilhaColuna1
                // chamar adicionar movimento
            }
            else
            {
                limpaMenu();
                gotoxy(1, 18);
                printf("Jogada invalida");
            }
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            break;
        case 'G':
            // ESCOLHEU MONTE 7
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
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            break;
        case 'G':
            // ESCOLHEU MONTE 7
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
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            break;
        case 'G':
            // ESCOLHEU MONTE 7
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
            break;
        case 'B':
            // ESCOLHEU MONTE 2
            break;
        case 'C':
            // ESCOLHEU MONTE 3
            break;
        case 'D':
            // ESCOLHEU MONTE 4
            break;
        case 'E':
            // ESCOLHEU MONTE 5
            break;
        case 'F':
            // ESCOLHEU MONTE 6
            break;
        case 'G':
            // ESCOLHEU MONTE 7
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void moveMesaMesa()
{

}

void moveMonteViradoParaMesa()
{
}

int verificarMoverMonteParaNaipe(TpPilha monteVirado,TpPilha pilhaOuro,TpPilha pilhaEspadas,TpPilha pilhaCopas,TpPilha pilhaPaus,int monte) {

    char figuras[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    tpCarta cartaTopoMonte = Pop(monteVirado);

    if(monte == 1) {
        tpCarta aux = Pop(pilhaOuro);
        if (buscaFigura(figuras,cartaTopoMonte.figura) > buscaFigura(figuras,aux.figura) && cartaTopoMonte.preto == aux.preto) {
            return 1;
        }
    }
    if (monte == 2) {
        tpCarta aux = Pop(pilhaEspadas);
        if (buscaFigura(figuras,cartaTopoMonte.figura) > buscaFigura(figuras,aux.figura) && cartaTopoMonte.preto == aux.preto) {
            return 1;
        }
    }
    if (monte == 3) {
        tpCarta aux = Pop(pilhaCopas);
        if (buscaFigura(figuras,cartaTopoMonte.figura) > buscaFigura(figuras,aux.figura) && cartaTopoMonte.preto == aux.preto) {
            return 1;
        }
    }
    if (monte == 4) {
        
        tpCarta aux = Pop(pilhaPaus);
        if (buscaFigura(figuras,cartaTopoMonte.figura) > buscaFigura(figuras,aux.figura) && cartaTopoMonte.preto == aux.preto) {
            return 1;
        }
        
    }
    return -1;
}

void moveMonteViradoParaNaipe(TpPilha monteVirado,TpPilha &pilhaOuros, TpPilha &pilhaEspadas, TpPilha &pilhaCopas, TpPilha &pilhaPaus) {
    printf("\nQual monte de naipes desejar mover essa carta (1-4)");
    
    int monte = scanf("%d",&monte);
    
    while(monte > 4 && monte<1) {
        printf("O numero do monte digitado nao existe");
        printf("Digite novamente: (1-4)");
        scanf("%d",&monte);
    }
    if(!Vazia(monteVirado.TOPO)) {
        if (verificarMoverMonteParaNaipe(monteVirado,pilhaOuros,pilhaEspadas,pilhaCopas,pilhaPaus,monte) != -1) {
            Push(pilhaPaus,Pop(monteVirado));
        }
        else {
            printf("A carta a ser movida deve ser do mesmo naipe e a proxima da sequencia!!");
        }
    }
    else {
        printf("Nao a nada no monte virado!!\n");
        gotoxy(1,18);
        system("pause");
        limpaMenu();
    }
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
        // jogar as cartas do monte virado pro monte normal, reembaralhar e puxar uma carta

        int qtasCartas = quantasCartasTemNaPilha(pilhaMonteVirado);
        tpCarta aux[qtasCartas];
        for (int i = 0; i < qtasCartas; i++)
            aux[i] = Pop(pilhaMonteVirado);

        srand(time(NULL));
        embaralhar(aux, qtasCartas);
        for (int j = 0; j < qtasCartas; j++)
        {
            Push(pilhaMonte, aux[j]);
        }
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
            // contagemDeMovimentos();
            break;
        case 'D':
            moveMesaMesa();
            // contagemDeMovimentos();
            break;
        case 'E':
            moveMonteViradoParaMesa();
            // contagemDeMovimentos();
            break;
        case 'F':
            moveMonteViradoParaNaipe(pilhaMonteVirado,pilhaOuros,pilhaEspadas,pilhaCopas,pilhaPaus);
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

int buscaFigura(char fig[13][3], char figBuscada[3])
{
    for (int i = 0; i < 13; i++)
        if (strcmp(fig[i], figBuscada) == 0)
            return i;
    return -1;
}

int verificaPodeEfeturarjogadaMoveNaipeMesa(TpPilha monteNaipe, TpPilha monteMesa)
{
    // verificar se carta do monte naipe pode entrar no monte mesa designado
    if (Vazia(monteNaipe.TOPO))
    {
        return 0;
    }
    char figuras[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    tpCarta cartaTopoMonteNaipe = Pop(monteNaipe), cartaTopoMonteMesa = Pop(monteMesa);
    if (buscaFigura(figuras, cartaTopoMonteNaipe.figura) > buscaFigura(figuras, cartaTopoMonteMesa.figura) ||
        cartaTopoMonteNaipe.preto == cartaTopoMonteMesa.preto)
    {
        return 0;
    }
    return 1;
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
