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
void ExbibirTemporarioSoVerPilha(TpPilha P);

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

void ExbibirTemporarioSoVerPilha(TpPilha P)
{
	tpCarta aux;
	while (!Vazia(P.TOPO))
	{
		aux = Pop(P);
		int cor, auxNaipe = aux.naipe;
		// fundo branco

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
		// gotoxy(fodac);
		printf("[%s]", aux.figura);
		textcolor(cor);
		textbackground(15);
		printf("[%c]", auxNaipe);
		textbackground(0);
		textcolor(15);
		printf("\n");
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
