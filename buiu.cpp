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

// declarao de funcoes
// auxiliares
void telaInicial();
void executar();
// mover cartas
void destribuirMesa();
void moveMesaTemp();
void moveTempMesa();
void moveMesaNaipe();
void moveNaipeTemp();
void moveTempNaipe();
void moveNaipeMesa();
void moveMesaMesa();
void popularPilhasColunas(TpPilha &monte, TpPilha &p1, TpPilha &p2, TpPilha &p3, TpPilha &p4, TpPilha &p5, TpPilha &p6, TpPilha &p7);
void inicializarMesa(
    TpPilha &pilhaMonte,
    TpPilha &pilhaMonteVirado,
    TpPilha &pilhaFixo1,
    TpPilha &pilhaFixo2,
    TpPilha &pilhaFixo3,
    TpPilha &pilhaFixo4,
    TpPilha &pilhaColuna1,
    TpPilha &pilhaColuna2,
    TpPilha &pilhaColuna3,
    TpPilha &pilhaColuna4,
    TpPilha &pilhaColuna5,
    TpPilha &pilhaColuna6,
    TpPilha &pilhaColuna7);
void criaBaralho(TpPilha &p);
void embaralhar(tpCarta *baralho, int n);

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
    // TpPilha aux[7] = {p1,
    //                   p2,
    //                   p3,
    //                   p4,
    //                   p5,
    //                   p6,
    //                   p7};
    // for (int i = 1; i <= 7; i++)
    // {
    //     printf("i %d", i);
    //     for (int j = 1; j <= i; j++)
    //     {
    //         printf(" j %d\n", i);
    //         Push(aux[i - 1], Pop(monte));
    //     }
    // }
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

    gotoxy(2, 24);
}

void inicializarMesa(
    TpPilha &pilhaMonte,
    TpPilha &pilhaMonteVirado,
    TpPilha &pilhaFixo1,
    TpPilha &pilhaFixo2,
    TpPilha &pilhaFixo3,
    TpPilha &pilhaFixo4,
    TpPilha &pilhaColuna1,
    TpPilha &pilhaColuna2,
    TpPilha &pilhaColuna3,
    TpPilha &pilhaColuna4,
    TpPilha &pilhaColuna5,
    TpPilha &pilhaColuna6,
    TpPilha &pilhaColuna7)
{
    // CRIAR BARALHO
    criaBaralho(pilhaMonte);
    // POPULAR PILHAS MONTE
    popularPilhasColunas(pilhaMonte, pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7);
    exibirInterfaceInicial(pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7);
    // CONFIRMAÇÃO
    // ExbibirTemporarioSoVerPilha(pilhaColuna1);
    // printf("\n");
    // ExbibirTemporarioSoVerPilha(pilhaColuna2);
    // printf("\n");
    // ExbibirTemporarioSoVerPilha(pilhaColuna3);
    // printf("\n");
    // ExbibirTemporarioSoVerPilha(pilhaColuna4);
    // printf("\n");
    // ExbibirTemporarioSoVerPilha(pilhaColuna5);
    // printf("\n");
    // ExbibirTemporarioSoVerPilha(pilhaColuna6);
    // printf("\n");
    // ExbibirTemporarioSoVerPilha(pilhaColuna7);
    // printf("\n");
    // fazer sistema de pontuação?
    // pode desfazer jogada?
    // popular PilhasColunas
}

void moveMesaFixo()
{
}

void moveTempMesa()
{
}

void moveMesaNaipe()
{
}

void moveTempNaipe()
{
}

void moveNaipeMesa()
{
}

void moveMesaMesa()
{
}

void executar()
{
    TpPilha pilhaMonte, pilhaMonteVirado, pilhaFixo1, pilhaFixo2, pilhaFixo3, pilhaFixo4, pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7;
    Inicializar(pilhaMonte);
    Inicializar(pilhaMonteVirado);
    Inicializar(pilhaFixo1);
    Inicializar(pilhaFixo2);
    Inicializar(pilhaFixo3);
    Inicializar(pilhaFixo4);
    Inicializar(pilhaColuna1);
    Inicializar(pilhaColuna2);
    Inicializar(pilhaColuna3);
    Inicializar(pilhaColuna4);
    Inicializar(pilhaColuna5);
    Inicializar(pilhaColuna6);
    Inicializar(pilhaColuna7);
    inicializarMesa(pilhaMonte, pilhaMonteVirado, pilhaFixo1, pilhaFixo2, pilhaFixo3, pilhaFixo4, pilhaColuna1, pilhaColuna2, pilhaColuna3, pilhaColuna4, pilhaColuna5, pilhaColuna6, pilhaColuna7);
    // inicializarMesa
}

int main()
{
    executar();

    return 0;
}
