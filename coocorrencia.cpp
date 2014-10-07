#include "coocorrencia.h"

Coocorrencia::Coocorrencia(int n)
{
    int i;
    NCo = n*n;
    OC = 0;
    precisao = 5;

    if(NCo<0)
    {
        cout << "Tamanho Invalido";
        return;
    }

    vF =new float[NCo];
    if(vF==NULL) exit(1);

    for(i=0;i<NCo;i++)
    {
        vF[i]=0.0;
    }
    //cout << "Vetor Construido com Sucesso!" << endl;
    ld = n;
}

Coocorrencia::~Coocorrencia()
{
    delete[] vF;
}

void Coocorrencia::vizinhoRight_Left_CPU(Vetor Imagem, int d)
{
    int i,j;
    int controle = 0;

    for(i=0;i<Imagem.NIm;i++)
    {
        for(j=1;j<=d;j++){
            if(((i+j)%Imagem.ld) == 0)
                controle = 1;
        }
        if(controle!=1)
        {
            vF[Imagem.vI[i]*ld + Imagem.vI[i+d]]++;
            OC++;
            vF[Imagem.vI[i+d]*ld + Imagem.vI[i]]++;
            OC++;
        }
        controle = 0;
    }
}

void Coocorrencia::vizinhoUp_Down_CPU(Vetor Imagem, int d)
{
    int i;
    for(i=Imagem.ld*d;i<Imagem.NIm;i++)
    {
        vF[Imagem.vI[i]*ld + Imagem.vI[i-(ld*d)]]++;
        OC++;
        vF[Imagem.vI[i-(ld*d)]*ld + Imagem.vI[i]]++;
        OC++;
    }
}

void Coocorrencia::vizinhoDiaUR_DiaDL_CPU(Vetor Imagem, int d)
{
    int i,j;
    int controle = 0;
    for(i=Imagem.ld*d;i<Imagem.NIm;i++)
    {
        for(j=1;j<=d;j++){
            if(((i+j)%Imagem.ld) == 0)
                controle = 1;
        }
        if(controle!=1)
        {
            vF[Imagem.vI[i]*ld + Imagem.vI[i-((ld-1)*d)]]++;
            OC++;
            vF[Imagem.vI[i-((ld-1)*d)]*ld + Imagem.vI[i]]++;
            OC++;
        }
        controle = 0;
    }
}

void Coocorrencia::vizinhoDiaUL_DiaDR_CPU(Vetor Imagem, int d)
{
    int i,j;
    int controle = 0;
    for(i=(Imagem.ld*d)+1;i<Imagem.NIm;i++)
    {
        for(j=1;j<=d;j++){
            if((((i-1)+j)%Imagem.ld) == 0)
                controle = 1;
        }
        if(controle!=1)
        {
            vF[Imagem.vI[i]*ld + Imagem.vI[i-((ld+1)*d)]]++;
            OC++;
            vF[Imagem.vI[i-((ld+1)*d)]*ld + Imagem.vI[i]]++;
            OC++;
        }
        controle = 0;
    }
}

void Coocorrencia::vizinhos_CPU(Vetor Imagem, int d)
{
    int i,j;
    int controle = 0;

    for(i=0;i<Imagem.NIm;i++)
    {
        // Angulo 0°
            for(j=1;j<=d;j++){
                if(((i+j)%Imagem.ld) == 0)
                    controle = 1;
            }
            if(controle!=1)
            {
                vF[Imagem.vI[i]*ld + Imagem.vI[i+d]]++;
                OC++;
                vF[Imagem.vI[i+d]*ld + Imagem.vI[i]]++;
                OC++;
            }
            controle = 0;
        if(i>=Imagem.ld*d)
        {
        // Angulo 90°

            vF[Imagem.vI[i]*ld + Imagem.vI[i-(ld*d)]]++;
            OC++;
            vF[Imagem.vI[i-(ld*d)]*ld + Imagem.vI[i]]++;
            OC++;

        // Angulo 45°

            for(j=1;j<=d;j++){
                if(((i+j)%Imagem.ld) == 0)
                    controle = 1;
            }
            if(controle!=1)
            {
                vF[Imagem.vI[i]*ld + Imagem.vI[i-((ld-1)*d)]]++;
                OC++;
                vF[Imagem.vI[i-((ld-1)*d)]*ld + Imagem.vI[i]]++;
                OC++;
            }
            controle = 0;

        // Angulo 135°

            for(j=1;j<=d;j++){
                if((((i-1)+j)%Imagem.ld) == 0)
                    controle = 1;
            }
            if(controle!=1)
            {
                vF[Imagem.vI[i]*ld + Imagem.vI[i-((ld+1)*d)]]++;
                OC++;
                vF[Imagem.vI[i-((ld+1)*d)]*ld + Imagem.vI[i]]++;
                OC++;
            }
            controle = 0;
        }
    }
}

void Coocorrencia::copia(Vetor Imagem)
{
    int i;
    for(i=0;i<NCo;i++)
        vF[i] = (float) Imagem.vI[i];
}

void Coocorrencia::normaliza()
{
    int i;
    float swap;
    for(i=0;i<NCo;i++)
        OC += vF[i];
    for(i=0;i<NCo;i++)
    {
        swap = (vF[i]/OC);
        vF[i] = swap;
    }
}

void Coocorrencia::imprimiCoo()
{
    int i;
    for(i=0;i<NCo;i++)
    {
        cout.setf(std::ios::fixed, std::ios::floatfield);
        cout.precision(precisao);
        cout << vF[i] << endl;
    }
}
