#include <iostream>
#include <cmath>

double f(double x);
template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps);

int main(int argc, char **argv)
{
    std::cout.precision(15); std::cout.setf(std::ios::scientific);

    const double XL = std::atof(argv[1]);
    const double XU = std::atof(argv[2]);
    const double EPS = std::atof(argv[3]);

    std::cout << bisection(XL, XU, f, EPS) << std::endl;

    return 0;
}

double f(double x)
{
    return 9.81 * (68.1) * (1 - std::exp(-x * 10 / 68.1)) / x - 40;
}

template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps)
{
    int iter = 0;
    double xr = 0;
    for (;;)
    {
        xr = (xl + xu) / 2; // Bisection
        // ¿Encontré la raíz?
        if (std::fabs(fun(xr)) < eps)
            break;
        iter++;

        // Actualiza los límites
        if (fun(xr) * fun(xl) < 0)
        {
            xu = xr;
        }
        else
        {
            xl = xr;
        }
    }

    return xr;
}