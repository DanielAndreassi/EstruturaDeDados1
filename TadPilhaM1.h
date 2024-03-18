#define MAXPILHA 10

struct TpPILHAM1
{
    int TOPO1,TOPO2;
    char PILHA[MAXPILHA];
};

void inicializar(TpPILHAM1 &PM) {
    PM.TOPO1=-1;
    PM.TOPO2=MAXPILHA;
} 

void PUSH(TpPILHAM1 &PM,int NP,char elemento) {
    if(NP==1) PM.PILHA[++PM.TOPO1]=elemento;
    
    else PM.PILHA[--PM.TOPO2] = elemento;
}

char POP(TpPILHAM1 &PM,int NP) {
    if(NP==1)  return PM.PILHA[PM.TOPO1--];
    
    return PM.PILHA[PM.TOPO2++];
}

char elementoTOPO(TpPILHAM1 PM,int NP) {
    if(NP == 1) return PM.PILHA[PM.TOPO1];
    
    else return PM.PILHA[PM.TOPO2];
}

int PMvazia(int topo,int NP) {
    if(NP == 1) return topo == -1;

    return topo==MAXPILHA;
}

int PMcheia(int topo1,int topo2) {
    return topo1 + 1 == topo2;
}

void exibirPilha(TpPILHAM1 PM,int NP) {
    if(NP==1) {
        while(!PMvazia(PM.TOPO1,NP)) {
            printf("%c\n",POP(PM,NP));
        }
    } 
    else {
        while(!PMvazia(PM.TOPO2,NP)) {
            printf("%c\n",POP(PM,NP));
        }
    }
}
