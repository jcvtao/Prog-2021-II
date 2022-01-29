/*
f'(X) = lim h-> 0 (f(x+h)-f(x))/h

f'(x, h) = (f(x+h)-f(x))/h + 0(h)
*/

#include <cmath>
#include <iostream>

double fun(double x);
double fderiv(double x, double h);

int main(int argc, char **argv)
{
    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    const double X = std::atof(argv[1]);

    for (double h = 1.0e-1; h >= 1.0e-15; h /= 10.0)
    {
        std::cout << h << "\t" << std::fabs(1 - fderiv(X, h)/std::cos(X)) << "\n";
    }
    return 0;
}

double fun(double x)
{
    return std::sin(x);
}

double fderiv(double x, double h)
{
    return (fun(x + h) - fun(x)) / h;
}