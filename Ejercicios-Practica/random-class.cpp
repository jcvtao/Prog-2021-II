#include <iostream>
#include <random>

// constantes
const unsigned long a = 1664525;
const unsigned long c = 1013904223;
const unsigned long m = 4294967296;
const unsigned long size = 3000;

unsigned long generateRandom(int x);

int main(void)
{
    std::vector<double> values (size, 0.0);

    // loop
    unsigned long seed = 1;
    for (int ii = 0; ii < size; ++ii)
    {
        unsigned long xa = generateRandom(seed);
        values[ii] = (1.0 * xa) / (m - 1);
        seed = xa;
    }

    //print
    for (int ii = 0; ii < size/3; ++ii)
    {
        std::cout << values[3*ii] << "\t"
                  << values[3*ii + 1] << "\t"
                  << values[3*ii + 2] << "\n";
    }

    /* terminal: ./a.out > data.txt
     * gnuplot: splot 'data.txt' w p
    */

    return 0;
}

unsigned long generateRandom(int x)
{
    unsigned long xf = ((a*x + c) % m);
    return xf;
}