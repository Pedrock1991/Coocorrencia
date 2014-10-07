#ifndef COOCORENCIA_H
#define COOCORENCIA_H
#include "vetor.h"

class Coocorrencia
{
public:
    int NCo;
    float *vF;
    int OC;
    int precisao;
    int ld;
public:
    Coocorrencia(int n);
    ~Coocorrencia();

    void vizinhoRight_Left_CPU(Vetor Imagem, int d);
    void vizinhoUp_Down_CPU(Vetor Imagem, int d);
    void vizinhoDiaUR_DiaDL_CPU(Vetor Imagem, int d);
    void vizinhoDiaUL_DiaDR_CPU(Vetor Imagem, int d);
    void vizinhos_CPU(Vetor Imagem, int d);
    void copia(Vetor Imagem);
    void normaliza();

    void imprimiCoo();
};

#endif // COOCORENCIA_H
