#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
bool is_idempotent(const std::vector<double> &M, const double eps);
int main(int arg, char *argv[])
{
    const int N = 4;
    const double EPS = std::atof(argv[1]);
    std::vector<double> A = {1.99, -2.01, -4,
                             -1, 2.999, 4,
                             0.999, -2, -3.01};
    std::cout << is_idempotent(A, EPS) << std::endl;
    return 0;
}
bool is_idempotent(const std::vector<double> &M, const double eps)
{
    bool answer = true;
    const int N = std::sqrt(M.size()); // N = 3; M = 3x3
    
    // calcule A*A, puede crear una nueva matriz
    std::vector<double> AA = {0.0};
    AA.resize(9); // A^2 = AA = 3x3

    for (int ii = 0; ii < N; ++ii)
    {
        for (int jj = 0; jj < N; ++jj)
        {
            double sum = 0.0;
            for (int kk = 0; kk < N; ++kk)
            {
                sum += M[ii * N + kk] * M[kk * N + jj]; // (ii, kk) * (kk, jj)
            }
            AA[ii * N + jj] = sum;
        }
    }

    // haga la resta A*A - A, para ir comparando cada elemento.
    for (int ii = 0; ii < N; ++ii)
    {
        for (int jj = 0; jj < N; ++jj)
        {
            // calcule la diferencia comparando con cero
            double diferencia = std::fabs(AA[ii*N + jj] - M[ii*N + jj]);
            if (0 < diferencia && diferencia > eps) // |A^2 - A| > \epsilon -> false
            {
                answer = false;
                return answer;
            }
        }
    }
    // retorne true o false de acuerdo a lo anterior
    return answer; // -> true
}