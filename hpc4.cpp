//addition

#include <iostream>
#include <cuda_runtime.h>

__global__ void vectorAdd(const float* A, const float* B, float* C, int N) {
    int i = threadIdx.x;
    if (i < N) C[i] = A[i] + B[i];
}

int main() {
    int N = 10;
    size_t size = N * sizeof(float);
    float *h_A, *h_B, *h_C, *d_A, *d_B, *d_C;
    
    cudaMallocHost(&h_A, size);
    cudaMallocHost(&h_B, size);
    cudaMallocHost(&h_C, size);
    
    for (int i = 0; i < N; i++) {
        h_A[i] = i * 1.0f;
        h_B[i] = i * 2.0f;
    }

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);
    
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    vectorAdd<<<1, N>>>(d_A, d_B, d_C, N);
    
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    std::cout << "A[i] + B[i] = C[i] results:\n";
    for (int i = 0; i < N; i++) {
        std::cout << h_A[i] << " + " << h_B[i] << " = " << h_C[i] << "\n";
    }

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    cudaFreeHost(h_A); cudaFreeHost(h_B); cudaFreeHost(h_C);
    
    return 0;
}


//mutiplication


#include <iostream>
#include <cuda_runtime.h>

__global__ void vectorMul(const float* A, const float* B, float* C, int N) {
    int i = threadIdx.x;
    if (i < N) C[i] = A[i] * B[i];
}

int main() {

    int N = 10;
    size_t size = N * sizeof(float);
    float *h_A, *h_B, *h_C, *d_A, *d_B, *d_C;

    cudaMallocHost(&h_A, size);
    cudaMallocHost(&h_B, size);
    cudaMallocHost(&h_C, size);

    for (int i = 0; i < N; i++) {
        h_A[i] = i * 1.0f;
        h_B[i] = i * 2.0f;
    }

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    vectorMul<<<1, N>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    std::cout << "A[i] * B[i] = C[i] results:\n";
    for (int i = 0; i < N; i++)
        std::cout << h_A[i] << " * " << h_B[i] << " = " << h_C[i] << "\n";

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    cudaFreeHost(h_A); cudaFreeHost(h_B); cudaFreeHost(h_C);

    return 0;
}

