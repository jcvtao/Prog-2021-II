#include <iostream>

int main()
{
    const long long int n = 600851475147;
    long long int divisor = 1;
    long long int ii = n - 1;

    for (ii; ii > 0; ii--)
    {
        if (n % ii == 0)
        {
            divisor = ii;
            break;          // Para salir del loop
        }
    }

    std::cout << "El divisor más grande de N = " << n << " es " << divisor << "\n";
    // El resultado tardó 1h 52m 2s en ser calculado.

    return 0;
}
