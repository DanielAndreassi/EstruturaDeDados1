#define MAXPILHA 52

struct tpCarta
{
	// 1 - OURO
	// 2 - ESPADA
	// 3 - COPAS
	// 4 - PAUS
	int naipe, preto;
	char figura[3];
};

struct TpPilha
{
	int TOPO;
	tpCarta PILHA[MAXPILHA];
};

void Inicializar(TpPilha &P);
void Push(TpPilha &P, tpCarta Elemento);
tpCarta Pop(TpPilha &P);
// void Exibir(TpPilha P);
char Vazia(int topo);
char Cheia(int topo);
tpCarta ElementoTopo(TpPilha P);
void ExbibirTemporarioSoVerPilha(TpPilha P, int colI, int linI, int mostrarSomenteTopo);

void Inicializar(TpPilha &P)
{
	P.TOPO = -1;
}

void Push(TpPilha &P, tpCarta Elemento)
{
	P.PILHA[++P.TOPO] = Elemento;
}

tpCarta Pop(TpPilha &P)
{
	return P.PILHA[P.TOPO--];
}

tpCarta ElementoTopo(TpPilha P)
{
	return P.PILHA[P.TOPO];
}

void ExbibirTemporarioSoVerPilha(TpPilha P, int colI, int linI, int tipoDePilha)
{
	// tipo 1 = pilhaColuna
	// tipo 2 = pilhaMonteVirado
	// tipo 3 = pilhaNaipe
	// exibir pilhaMonteVirado max 5

	tpCarta aux;
	if (tipoDePilha == 3)
	{
		aux = Pop(P);
		int cor, auxNaipe = aux.naipe;
		switch (auxNaipe)
		{
		case 1:
			// cor vermelho
			cor = 4;
			auxNaipe = 4;
			break;
		case 2:
			// cor preto
			cor = 0;
			auxNaipe = 6;
			break;
		case 3:
			cor = 4;
			auxNaipe = 3;
			break;
		case 4:
			// cor preto
			cor = 0;
			auxNaipe = 5;
			break;
		}
		// textcolor(cor);
		// textbackground(15);
		gotoxy(colI, linI);
		printf("[%s]", aux.figura);
		textcolor(cor);
		textbackground(15);
		printf("[%c]", auxNaipe);
		textbackground(0);
		textcolor(15);
	}
	else if (tipoDePilha == 1)
	{
		int qteCartas = P.TOPO;
		int linhaAux = qteCartas + linI;
		while (!Vazia(P.TOPO))
		{
			aux = Pop(P);
			int cor, auxNaipe = aux.naipe;
			switch (auxNaipe)
			{
			case 1:
				// cor vermelho
				cor = 4;
				auxNaipe = 4;
				break;
			case 2:
				// cor preto
				cor = 0;
				auxNaipe = 6;
				break;
			case 3:
				cor = 4;
				auxNaipe = 3;
				break;
			case 4:
				// cor preto
				cor = 0;
				auxNaipe = 5;
				break;
			}
			// textcolor(cor);
			// textbackground(15);
			gotoxy(colI, linhaAux);
			printf("[%s]", aux.figura);
			textcolor(cor);
			textbackground(15);
			printf("[%c]", auxNaipe);
			linhaAux--;
			textbackground(0);
			textcolor(15);
		}
	}
	else
	{
		// IMPLEMENTAR PRINT pilhaMonteVirado
		int qteCartas = P.TOPO;
		int linhaAux = qteCartas > 4 ? linI + 4 : qteCartas + linI;
		while (!Vazia(P.TOPO) && P.TOPO > qteCartas - 5)
		{
			aux = Pop(P);
			int cor, auxNaipe = aux.naipe;
			switch (auxNaipe)
			{
			case 1:
				// cor vermelho
				cor = 4;
				auxNaipe = 4;
				break;
			case 2:
				// cor preto
				cor = 0;
				auxNaipe = 6;
				break;
			case 3:
				cor = 4;
				auxNaipe = 3;
				break;
			case 4:
				// cor preto
				cor = 0;
				auxNaipe = 5;
				break;
			}
			// textcolor(cor);
			// textbackground(15);
			gotoxy(colI, linhaAux);
			printf("[%s]", aux.figura);
			textcolor(cor);
			textbackground(15);
			printf("[%c]", auxNaipe);
			linhaAux--;
			textbackground(0);
			textcolor(15);
		}
	}
}

// void Exibir(TpPilha P)
//{
//  while (!Vazia(P.TOPO))
//  	printf("\n%c",Pop(P));
//  IMPLEMENTAR
//}

char Vazia(int topo)
{
	return (topo == -1);
}

char Cheia(int topo)
{
	return (topo == MAXPILHA - 1);
}
