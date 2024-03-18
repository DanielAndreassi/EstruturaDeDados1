#define MAXPILHA 10

struct TpPilha
{
	int TOPO;
	char PILHA[MAXPILHA];
};

/*Inicializa��o da estrutura;
Insere na pilha; (PUSH)
Retira da pilha; (POP)
Retorna elemento do TOPO;
Verifica se PILHA cheia;
Verifica se PILHA vazia;
Exibe a Pilha;*/

//Opera��es Associadas
void Inicializar(TpPilha &P);
void Push(TpPilha &P, char Elemento);
char Pop(TpPilha &P);
char ElementoTopo(TpPilha P);
void Exibir(TpPilha P);
char Vazia(int topo);
char Cheia(int topo);

void Inicializar(TpPilha &P)
{
	P.TOPO = -1;
}

void Push(TpPilha &P, char Elemento)
{
	P.PILHA[++P.TOPO] = Elemento;
}

char Pop(TpPilha &P)
{
	return P.PILHA[P.TOPO--];
}

char ElementoTopo(TpPilha P)
{
	return P.PILHA[P.TOPO];
}

void Exibir(TpPilha P)
{
	while (!Vazia(P.TOPO))
		printf("\n%c",Pop(P));
}

char Vazia(int topo)
{
	return (topo == -1);
}

char Cheia(int topo)
{
	return (topo == MAXPILHA-1);
}

