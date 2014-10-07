#include "operacoes.h"

Operacoes::Operacoes()
{
    med = 0.0;
    max =-2.0;
    min = 1.0;
}

Operacoes::~Operacoes()
{

}

void Operacoes::media_CPU(Coocorrencia coocorrencia)
{
    med = coocorrencia.OC/coocorrencia.NCo;
    cout << "A media é: " << med << endl;
}

void Operacoes::maximo_CPU(Coocorrencia coocorrencia)
{
    int i;
    for(i=0;i<coocorrencia.NCo;i++)
    {
        if(coocorrencia.vF[i]>max)
            max = coocorrencia.vF[i];
    }
    cout << "O maximo é: " << max << endl;
}

void Operacoes::minimo_CPU(Coocorrencia coocorrencia)
{
    int i;
    for(i=0;i<coocorrencia.NCo;i++)
    {
        if(coocorrencia.vF[i]<min)
            min = coocorrencia.vF[i];
    }
    cout << "O minimo é: " << min << endl;
}

void Operacoes::media_maximo_minimo(Coocorrencia coocorrencia)
{
    int i;
    min = 1.0;
    for(i=0;i<coocorrencia.NCo;i++)
    {
        soma += coocorrencia.vF[i];
        if(coocorrencia.vF[i]<min)
            min = coocorrencia.vF[i];
        if(coocorrencia.vF[i]>max)
            max = coocorrencia.vF[i];
    }
    med = soma/coocorrencia.NCo;

    cout << "A media é: " << med << endl;
    cout << "O maximo é: " << max << endl;
    cout << "O minimo é: " << min << endl;

}
