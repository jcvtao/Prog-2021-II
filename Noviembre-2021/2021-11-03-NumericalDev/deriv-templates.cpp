#include <cmath>
#include <iostream>

// double (*f) (double);
using fptr = double(double);

double fun(double x);
double g(double x);
double forward(double x, double h, fptr f);
double central(double x, double h, fptr f);

template <typename typefun, typename typealg>   // Define template names
double trichardson(double x, double h, typefun f, typealg alg)
{
    double val1 = alg(x, h, f);
    double val2 = alg(x , h/2, f);
    return (4 * val2 - 1) / 3;
}

int main(int argc, char **argv)
{
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);
    const double X = std::atof(argv[1]);

    for (double h = 1.0e-1; h >= 1.0e-15; h /= 10.0)
    {
        std::cout << h << "\t"
                  << std::fabs(1 - forward(X, h, fun) / std::cos(X)) << "\t"
                  << std::fabs(1 - central(X, h, fun) / std::cos(X)) << "\t"
                  << std::fabs(1 - trichardson(X, h, fun, forward) / std::cos(X)) << "\t"
                  << std::fabs(1 - trichardson(X, h, fun, central) / std::cos(X)) << "\n";
    }
    return 0;
}

double fun(double x)
{
    return std::sin(x);
}

double g(double x)
{
    return x * x;
}

double forward(double x, double h, fptr f)
{
    return (f(x + h) - f(x)) / h;
}

double central(double x, double h, fptr f)
{
    return (f(x + h) - f(x - h)) / (2 * h);
}