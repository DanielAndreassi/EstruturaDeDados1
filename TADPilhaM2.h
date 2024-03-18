#define MAXPILHA 10

struct TpPilhaM2
{
    int TOPO[MAXPILHA], BASE[MAXPILHA];
    char PILHA[MAXPILHA];
};

void inicializar(TpPilhaM2 &PM,int qtde) {
    int qtdeElementos=MAXPILHA/qtde;
    
    for(int i=0;i<qtde;i++) {
        PM.BASE[i] = i*qtdeElementos;
        PM.TOPO[i] = PM.BASE[i]-1;
    }
}

void PUSH(TpPilhaM2 &PM,char elem,int NP) {
    PM.PILHA[++PM.TOPO[NP]] = elem;
}

char POP(TpPilhaM2 &PM,int NP) {
    return PM.PILHA[PM.TOPO[NP]--];
}

char elementoTopo(TpPilhaM2 PM,int NP) {
    return PM.PILHA[PM.TOPO[NP]];
}

int cheia(TpPilhaM2 PM,int NP) {
    return PM.TOPO[NP] == PM.BASE[NP+1]-1;
    //return PM.TOPO[NP]+1 == PM.BASE[NP+1];
}

int vazia(TpPilhaM2 PM,int NP) {
    return PM.TOPO[NP]+1 == PM.BASE[NP];
}

void exibir(TpPilhaM2 PM,int NP) {
    while(!vazia(PM,NP)) {
        printf("\n%c",POP(PM,NP));
    } 
}