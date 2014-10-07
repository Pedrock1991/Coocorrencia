#ifndef OPERACOES_H
#define OPERACOES_H
#include "coocorrencia.h"
#include <iostream>

using namespace std;

class Operacoes
{
public:
    float med;
    float max;
    float min;
    float soma;
public:
    Operacoes();
    ~Operacoes();
    void media_CPU(Coocorrencia coocorrencia);
    void maximo_CPU(Coocorrencia coocorrencia);
    void minimo_CPU(Coocorrencia coocorrencia);
    void media_maximo_minimo(Coocorrencia coocorrencia);
};

#endif // OPERACOES_H
