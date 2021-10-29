#include <iostream>
#include <cmath>

// Declaration
bool isprime(long long n);
long long largestprimedivisor(long long n);
long long sumprimedivisors(long long n);

int main(void)
{
    const long long N = 600851475147;
    std::cout << largestprimedivisor(N) << std::endl;
    std::cout << std::endl << "Divisores primos de " << N << ":" << std::endl;
    std::cout << sumprimedivisors(N) << std::endl;

    return 0;
}

// Implementation
long long largestprimedivisor(long long n)
{
    long long result = 0;
    for (long long int ii = 2 ; ii <= n/2 ; ii++)
    {
        if (n % ii == 0)
        {
            long long largedivisor = n / ii;
            if (isprime(largedivisor))
            {
                result = largedivisor;
                break;
            }
        }
    }
    std::cout << "El divisor primo más grande de " << n << " es ";
    return result;
}

long long sumprimedivisors(long long n)
{
    long long sum = 0;
    long long limit = n / 2;
    for (long long int ii = 2 ; ii <= limit ; ii++)
    {
        if (n % ii == 0 && isprime(ii))
        {
            sum += ii;
            limit = n / ii;
            std::cout << "- " << ii << std::endl;
        }
    }
    std::cout << std::endl << "Suma: "; // Resultado
    return sum;
}

bool isprime(long long n)
{
    bool isprime = true;
    for (long long jj = 2 ; jj <= std::sqrt(n) ; jj++)
    {
        if (n % jj == 0)
        {
            isprime = false;
            break;
        }
    }
    return isprime;
}