#include <QCoreApplication>
#include <iostream>
#include <CL/cl.h>
#include <CL/opencl.h>
#include <oclUtils.h>
#include "coocorrencia.h"
#include "operacoes.h"

using namespace std;

cl_int error = 0;   // Used to handle error codes
cl_platform_id platform;
cl_context context;
cl_command_queue queue;
cl_device_id device;
cl_program program;

unsigned int tamanhoImagem = 2000;
unsigned int niveisCinza = 4;
unsigned int distancia = 2;

void initialize_GPU();
void initialize_Program();
void launching_Kernel(cl_kernel, int);

int main()
{
    // Indentify and initialize GPU
    initialize_GPU();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Creates the variables and initialize both vectors

    Vetor imagem(tamanhoImagem);
    Vetor ocorrencia(niveisCinza);

    imagem.preenche(1,1);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Allocates buffer size
    const int mem_imagem = sizeof(int)*(tamanhoImagem*tamanhoImagem);
    const int mem_ocorrencia = sizeof(int)*(niveisCinza*niveisCinza);

    // Allocates a buffer of size mem_imagem and copies mem_imagem bytes from imagem
    cl_mem imagemGPU = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mem_imagem, imagem.vI, &error);
    // Allocates a buffer of size mem_ocorrencia and copies mem_ocorrencia bytes from ocorrencia
    cl_mem ocorrenciaGPU = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, mem_ocorrencia, ocorrencia.vI, &error);

    // Creates the program
    initialize_Program();

    // Extracting the kernel
    cl_kernel ocorrencia_kernel = clCreateKernel(program, "vizinhos_GPU", &error);
    assert(error == CL_SUCCESS);

    // Enqueuing parameters
    // Note that we inform the size of the cl_mem and cl_int object, not the size of the memory pointed by it
    error = clSetKernelArg(ocorrencia_kernel, 0, sizeof(cl_mem), &imagemGPU);
    error = clSetKernelArg(ocorrencia_kernel, 1, sizeof(cl_mem), &ocorrenciaGPU);
    error = clSetKernelArg(ocorrencia_kernel, 2, sizeof(cl_int), &ocorrencia.ld);
    error = clSetKernelArg(ocorrencia_kernel, 3, sizeof(cl_int), &imagem.ld);
    error = clSetKernelArg(ocorrencia_kernel, 4, sizeof(cl_int), &distancia);
    assert(error == CL_SUCCESS);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Launching kernel
    launching_Kernel(ocorrencia_kernel, 512);

    // Reading back

    Vetor buff(niveisCinza);
    clEnqueueReadBuffer(queue, ocorrenciaGPU, CL_TRUE, 0, mem_ocorrencia, buff.vI, 0, NULL, NULL);

    Coocorrencia coocorrencia_GPU(niveisCinza), coocorrencia_CPU(niveisCinza);
    buff.imprimiImagem();
    coocorrencia_GPU.copia(buff);
    coocorrencia_GPU.normaliza();
    coocorrencia_GPU.imprimiCoo();

    Operacoes Control;

    Control.media_maximo_minimo(coocorrencia_GPU);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Cleaning up
    imagem.~Vetor();
    ocorrencia.~Vetor();
    buff.~Vetor();
    coocorrencia_GPU.~Coocorrencia();
    coocorrencia_CPU.~Coocorrencia();
    clReleaseKernel(ocorrencia_kernel);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    clReleaseMemObject(imagemGPU);
    clReleaseMemObject(ocorrenciaGPU);

}

// Function to initialize: Platform, Device, Context and Command-queue
void initialize_GPU()
{
    // Platform
    error = oclGetPlatformID(&platform);
    if (error != CL_SUCCESS) {
       cout << "Error getting platform id: " << error << endl;
       exit(error);
    }
    // Device
    error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if (error != CL_SUCCESS) {
       cout << "Error getting device ids: " << error << endl;
       exit(error);
    }
    // Context
    context = clCreateContext(0, 1, &device, NULL, NULL, &error);
    if (error != CL_SUCCESS) {
       cout << "Error creating context: " << error << endl;
       exit(error);
    }
    // Command-queue
    queue = clCreateCommandQueue(context, device, 0, &error);
    if (error != CL_SUCCESS) {
       cout << "Error creating command queue: " << error << endl;
       exit(error);
    }
}

// Function to create and make the Program
void initialize_Program()
{
    // Creates the program
    // Uses NVIDIA helper functions to get the code string and it's size (in bytes)
    size_t src_size = 0;
    const char* path = shrFindFilePath("ocorrencia.cl", NULL);
    const char* source = oclLoadProgSource(path, "", &src_size);
    program = clCreateProgramWithSource(context, 1, &source, &src_size, &error);
    assert(error == CL_SUCCESS);

    // Builds the program
    error = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    assert(error == CL_SUCCESS);
}

// Function to lauching and run the kernel
void launching_Kernel(cl_kernel kernel, int nThreads)
{
    // Launching kernel
    const size_t local_ws = nThreads;	// Number of work-items per work-group
    // shrRoundUp returns the smallest multiple of local_ws bigger than size
    const size_t global_ws = shrRoundUp(local_ws, tamanhoImagem*tamanhoImagem);	// Total number of work-items
    error = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_ws, &local_ws, 0, NULL, NULL);
    assert(error == CL_SUCCESS);
}
