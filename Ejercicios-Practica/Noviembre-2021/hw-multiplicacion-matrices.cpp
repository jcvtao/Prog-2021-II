#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>

void multiply(const std::vector<double> &m1, const std::vector<double> &m2, std::vector<double> &m3);
void table_tiempos(int seed);

int main(int argc, char **argv)
{
    // read parameters
    const int N = std::atoi(argv[1]);
    const int SEED = std::atoi(argv[2]);

    // data structs
    std::vector<double> A(N * N, 0.0), B(N * N, 0.0), C(N * N, 0.0);

    // fill matrices A and B, using random numbers betwwen 0 and 1
    std::mt19937 gen(SEED);
    std::uniform_real_distribution<> dist(0., 1.);
    // lambda function: a local function that captures [] something, receives something (), and return something {}
    // See: https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/
    std::generate(A.begin(), A.end(), [&gen, &dist]() { return dist(gen); }); // uses a lambda function
    std::generate(B.begin(), B.end(), [&gen, &dist]() { return dist(gen); }); // uses a lambda function

    // multiply the matrices A and B and save the result into C. Measure time
    auto start = std::chrono::high_resolution_clock::now();
    multiply(A, B, C);
    auto stop = std::chrono::high_resolution_clock::now();

    // use the matrix to avoid the compiler removing it
    std::cout << C[N / 2] << std::endl;

    // print time
    auto elapsed = std::chrono::duration<double>(stop - start);
    std::cout << elapsed.count() << "\n";

    // tabla de tiempo vs tamaño matrices
    table_tiempos(SEED);

    return 0;
}

// implementations
void multiply(const std::vector<double> &m1, const std::vector<double> &m2, std::vector<double> &m3)
{
    const int N = std::sqrt(m1.size()); // assumes square matrices

    for (int ii = 0; ii < N; ++ii) {
        for (int jj = 0; jj < N; ++jj) {
            double sum = 0.0;
            for (int kk = 0; kk < N; ++kk) {
                sum += m1[ii * N + kk] * m2[kk * N + jj]; // (ii, kk) * (kk, jj)
            }
            m3[ii * N + jj] = sum;
        }
    }
}

// Función es para generar la tabla de timepos de ejecución en función del tamaño de las matrices, en el archivo "tiempos.txt"
void table_tiempos(int seed)
{
    std::ofstream fout("tiempos.txt");

    // Para N = 4
        std::mt19937 gen(seed);
        std::uniform_real_distribution<> dist(0., 1.);
    
        std::vector<double> A(4 * 4, 0.0), B(4 * 4, 0.0), C(4 * 4, 0.0);
        std::generate(A.begin(), A.end(), [&gen, &dist]() { return dist(gen); });
        std::generate(B.begin(), B.end(), [&gen, &dist]() { return dist(gen); });

        auto start = std::chrono::high_resolution_clock::now();
        multiply(A, B, C);
        auto stop = std::chrono::high_resolution_clock::now();

        // Tiempo normalizado para el tamaño N = 4
        auto timeN4 = std::chrono::duration<double>(stop - start);
        fout << 4 << "\t" << 1.000 << "\n";
    
    // Para N = 8, 16, 32, ...
        for (int nn = 8; nn <= 512; nn *= 2)
        {
            std::vector<double> A(nn * nn, 0.0), B(nn * nn, 0.0), C(nn * nn, 0.0);
            std::generate(A.begin(), A.end(), [&gen, &dist]() { return dist(gen); });
            std::generate(B.begin(), B.end(), [&gen, &dist]() { return dist(gen); });

            auto start = std::chrono::high_resolution_clock::now();
            multiply(A, B, C);
            auto stop = std::chrono::high_resolution_clock::now();
            auto timeN = std::chrono::duration<double>(stop - start);

            fout << nn << "\t" << timeN.count()/timeN4.count() << "\n";
    }
}