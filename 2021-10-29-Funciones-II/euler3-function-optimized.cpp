#include <iostream>
#include <cmath>

// Declaration
bool isprime(long long n);
long long largestprimedivisor(long long n);

int main(void)
{
    const long long N = 600851475143;
    std::cout << largestprimedivisor(N) << std::endl;

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
    return result;
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