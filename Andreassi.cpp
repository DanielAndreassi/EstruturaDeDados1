#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#include <conio2.h>

// todas os conceitos de pilha estao nos include, pilha normal,listas concorrentes(TADPilhaM1) e pilhas multiplas(TADPilhaM2)
#include "TADPilha.h"
#include "TadPilhaM1.h"
#include "TADPilhaM2.h"

// declarao de funcoes
//auxiliares
void telaInicial();
void executar();
//mover cartas
void destribuirMesa();
void moveMesaTemp();
void moveTempMesa();
void moveMesaNaipe();
void moveNaipeTemp();
void moveTempNaipe();
void moveNaipeMesa();
void moveMesaMesa();
//funcoes


void destribuirMesa() {

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

void moveMesaTemp() {
}

void moveTempMesa() {

}

void moveMesaNaipe() {

}

void moveNaipeTemp() {
}

void moveTempNaipe() {

}

void moveNaipeMesa() {

}

void moveMesaMesa() {

}

void executar()
{
    telaInicial();
}

int main()
{
    executar();
    return 0;
}
