#pragma OPENCL EXTENSION cl_khr_local_int64_base_atomics : enable


__kernel void vizinhoRight_Left_GPU(global int* Imagem, global int* Ocorrencia, int tamLinha, int tamImagem, int distancia){

        int i = get_global_id(0);
        int controle = 0;
        int tam = tamImagem*tamImagem;

        for(int j=1;j<=distancia;j++)
        {
            if(((i+j)%tamImagem) == 0)
            {
                controle = 1;
            }
        }
        if(controle!=1)
        {
            if(i < tam)
            {
                atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i+distancia]],1);
                atomic_add(&Ocorrencia[Imagem[i+distancia]*tamLinha + Imagem[i]],1);
            }
        }
        controle = 0;
}

__kernel void vizinhoUp_Down_GPU(global int* Imagem, global int* Ocorrencia, int tamLinha, int tamImagem, int distancia){

        int i = get_global_id(0);
        int tam = tamImagem*tamImagem;
        int op = tamLinha*distancia;

        if(i < tam)
        {
            if(i>=tamLinha*distancia){
                atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i-op]],1);
                atomic_add(&Ocorrencia[Imagem[i-op]*tamLinha + Imagem[i]],1);
            }
        }
}

__kernel void vizinhoDiaUR_DiaDL_GPU(global int* Imagem, global int* Ocorrencia, int tamLinha, int tamImagem, int distancia){

        int i = get_global_id(0);
        int tam = tamImagem*tamImagem;
        int op = (tamLinha-1)*distancia;
        int controle = 0;

        for(int j=1;j<=distancia;j++)
        {
            if(((i+j)%tamImagem) == 0)
            {
                controle = 1;
            }
        }

        if(controle!=1)
        {
            if(i < tam)
            {
                if(i>=tamImagem*distancia)
                {
                    atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i-op]],1);
                    atomic_add(&Ocorrencia[Imagem[i-op]*tamLinha + Imagem[i]],1);
                }

            }
        }
        controle = 0;
}

__kernel void vizinhoDiaUL_DiaDR_GPU(global int* Imagem, global int* Ocorrencia, int tamLinha, int tamImagem, int distancia){

        int i = get_global_id(0);
        int tam = tamImagem*tamImagem;
        int op = (tamLinha+1)*distancia;
        int controle = 0;

        for(int j=1;j<=distancia;j++)
        {
            if((((i-1)+j)%tamImagem) == 0)
            {
                controle = 1;
            }
        }

        if(controle!=1)
        {
            if(i < tam)
            {
                if(i>=tamImagem*distancia)
                {
                    atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i-op]],1);
                    atomic_add(&Ocorrencia[Imagem[i-op]*tamLinha + Imagem[i]],1);
                }
            }
        }
        controle = 0;
}

__kernel void vizinhos_GPU(global int* Imagem, global int* Ocorrencia, int tamLinha, int tamImagem, int distancia){
        int i = get_global_id(0);
        int tam = tamImagem*tamImagem;
        int op;
        int controle = 0;
        int j;

        if(i < tam)
        {
            // Angulo 0°
            for(j=1;j<=distancia;j++)
            {
                if(((i+j)%tamImagem) == 0)
                {
                    controle = 1;
                }
            }
            if(controle!=1)
            {
                atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i+distancia]],1);
                atomic_add(&Ocorrencia[Imagem[i+distancia]*tamLinha + Imagem[i]],1);
            }
            controle = 0;

            // Angulo 90°
            op = tamLinha*distancia;
            if(i>=tamLinha*distancia)
            {
                atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i-op]],1);
                atomic_add(&Ocorrencia[Imagem[i-op]*tamLinha + Imagem[i]],1);
            }

            if(i>=tamImagem*distancia)
            {
                // Angulo 45°
                op = (tamLinha-1)*distancia;
                for(j=1;j<=distancia;j++)
                {
                    if(((i+j)%tamImagem) == 0)
                    {
                        controle = 1;
                    }
                }

                if(controle!=1)
                {
                    atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i-op]],1);
                    atomic_add(&Ocorrencia[Imagem[i-op]*tamLinha + Imagem[i]],1);
                }
                controle = 0;

                // Angulo 135°
                op = (tamLinha+1)*distancia;
                for(j=1;j<=distancia;j++)
                {
                    if((((i-1)+j)%tamImagem) == 0)
                    {
                        controle = 1;
                    }
                }

                if(controle!=1)
                {
                    atomic_add(&Ocorrencia[Imagem[i]*tamLinha + Imagem[i-op]],1);
                    atomic_add(&Ocorrencia[Imagem[i-op]*tamLinha + Imagem[i]],1);
                }
                controle = 0;
            }
        }
}
