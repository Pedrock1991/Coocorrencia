#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vetor.h"

Vetor::Vetor(int n)
{
    int i;
    NIm = n*n;

    if(NIm<0)
    {
        cout << "Tamanho Invalido" << endl;
        return;
    }

    vI =new int[NIm];
    if(vI==NULL) exit(1);

    for(i=0;i<NIm;i++)
    {
        vI[i]=0;
    }
    //cout << "Vetor Construido com Sucesso!" << endl;
    ld = n;
}

Vetor::~Vetor()
{
    delete[] vI;
}

void Vetor::imprimiImagem()
{
    int i;
    for(i=0;i<NIm;i++)
    {
        cout << vI[i] << endl;
    }
}

void Vetor::preenche(int superior, int inferior)
{
    int i;
    for(i=0;i<NIm;i++)
    {
        vI[i] = (rand() % (superior-inferior+1))+inferior;
    }
}
