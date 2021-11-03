#include <cmath>
#include <iostream>

// double (*f) (double);
using fptr = double(double);        // Puntero a función

double fun(double x);
double g(double x);
double forward(double x, double h, fptr f);

int main(int argc, char **argv)
{
    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    const double X = std::atof(argv[1]);

    for (double h = 1.0e-1; h >= 1.0e-15; h /= 10.0)
    {
        std::cout << h << "\t" << std::fabs(1 - forward(X, h, g)/std::cos(X)) << "\n";
    }
    return 0;
}

double fun(double x)
{
    return std::sin(x);
}

double g(double x)
{
    return x*x;
}

double forward(double x, double h, fptr f)
{
    return (f(x+h) - f(x))/h;
}