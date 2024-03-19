#define MAXPILHA 52

struct tpCarta
{
	int naipe, preto, virada;
	char figura;
};

struct TpPilha
{
	int TOPO;
	tpCarta PILHA[MAXPILHA];
};

void Inicializar(TpPilha &P);
void Push(TpPilha &P, tpCarta Elemento);
tpCarta Pop(TpPilha &P);
tpCarta Exibir(TpPilha P);
char Vazia(int topo);
char Cheia(int topo);

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

//void Exibir(TpPilha P)
//{
	// while (!Vazia(P.TOPO))
	// 	printf("\n%c",Pop(P));
	// IMPLEMENTAR
//}

char Vazia(int topo)
{
	return (topo == -1);
}

char Cheia(int topo)
{
	return (topo == MAXPILHA - 1);
}
