#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>  // Para pthreads

const int SIZE = 400;

struct ThreadData {
    const int (*A)[SIZE];
    const int (*B)[SIZE];
    int (*result)[SIZE];
};

void fillMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = rand() % 2;
        }
    }
}

void printMatrix(const int matrix[SIZE][SIZE], const char* name) {
    std::cout << "Matrix " << name << ":\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void* sumMatrices(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            data->result[i][j] = data->A[i][j] + data->B[i][j];
        }
    }
    pthread_exit(nullptr);
}

void* subtractMatrices(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            data->result[i][j] = data->A[i][j] - data->B[i][j];
        }
    }
    pthread_exit(nullptr);
}

void multiplyMatrices(const int A[SIZE][SIZE], const int B[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;  // Inicializar en 0
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    std::srand(std::time(0)); // Inicializar la semilla aleatoria

    int A[SIZE][SIZE], B[SIZE][SIZE];
    int sumResult[SIZE][SIZE], diffResult[SIZE][SIZE], finalResult[SIZE][SIZE];

    fillMatrix(A);
    fillMatrix(B);

    ThreadData sumData = {A, B, sumResult};
    ThreadData diffData = {A, B, diffResult};

    pthread_t sumThread, diffThread;

    pthread_create(&sumThread, nullptr, sumMatrices, (void*)&sumData);
    pthread_create(&diffThread, nullptr, subtractMatrices, (void*)&diffData);

    pthread_join(sumThread, nullptr);
    pthread_join(diffThread, nullptr);

    multiplyMatrices(sumResult, diffResult, finalResult);
    
    /*printMatrix(finalResult, "Final ( (A+B) * (A-B) )");*/

    return 0;
}
