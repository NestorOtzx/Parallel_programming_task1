#include <iostream>
#include <cstdlib>
#include <ctime>

const int SIZE = 400;

// Función para llenar una matriz con valores binarios aleatorios (0 o 1)
void fillMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = rand() % 2;
        }
    }
}

// Función para imprimir una matriz
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

// Función para sumar dos matrices
void sumMatrices(const int A[SIZE][SIZE], const int B[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Función para restar dos matrices
void subtractMatrices(const int A[SIZE][SIZE], const int B[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Función para multiplicar dos matrices
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

    sumMatrices(A, B, sumResult);
    
    subtractMatrices(A, B, diffResult);

    multiplyMatrices(sumResult, diffResult, finalResult);

    /*printMatrix(finalResult, "Final ( (A+B) * (A-B) )");*/

    return 0;
}
