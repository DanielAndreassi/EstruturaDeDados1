#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#include <conio2.h>

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
void criabaralho(TpPilha &p);
void embaralhar(tpCarta *baralho, int n);
// funcoes

void criabaralho(TpPilha &p)
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

void destribuirMesa()
{
}

void telaInicial()
{
    system("cls");

    textcolor(WHITE); // Muda a cor do texto para branca

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
}

int main()
{
    executar();
    return 0;
}
