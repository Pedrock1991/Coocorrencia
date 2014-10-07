#include <iostream>
#include <stdlib.h>


using namespace std;

class Vetor
{
public:
    int NIm;
    int ld;
    //int OC;
    int *vI;
    //float *vF;
public:
    Vetor(int n);
    //void inicializaFlo(int n);

    ~Vetor();
    //void deletaFlo();

    void imprimiImagem();
    //void imprimiFlo();
    void preenche(int superior, int inferior);

    //void vizinhoDir_Esq(Vetor Imagem, int d);
    //void vizinhoUp_Down(Vetor Imagem, int d);
    //void vizinhoDiaUD_DiaDE(Vetor Imagem, int d);
    //void vizinhoDiaUE_DiaDD(Vetor Imagem, int d);

    //void normalize();
};


