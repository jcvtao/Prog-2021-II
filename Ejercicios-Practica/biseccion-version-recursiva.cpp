#include <iostream>
#include <cmath>
#include <cstdlib>

double f(double x);
template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps, int &niter);
template <class fptr2>
double bisection_recursivo(double xl, double xu, fptr2 fun, double eps, int &niter);

int main(int argc, char **argv)
{
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);
    const double XL = std::atof(argv[1]);
    const double XU = std::atof(argv[2]);
    const double EPS = std::atof(argv[3]);

    std::cout << "bisection\t\titer\tbisection_recursivo\titer2\n";
              //<< "-------\t\t\t---------\t\t-------------------\t-----------\n";

    
    for (double eps = EPS ; eps > 1e-6 ; eps /= 10)
    {
        int counter = 0;
        int counter2 = 0;
        std::cout << bisection(XL, XU, f, eps, counter) << "\t"
                  << counter << "\t"
                  << bisection_recursivo(XL, XU, f, eps, counter2) << "\t"
                  << counter2 << "\n";
    }
    

    //int counter = 0;
    //std::cout << EPS << "\t" << bisection(XL, XU, f, EPS, counter) << "\t" << bisection_recursivo(XL, XU, f, EPS) << "\t";
    //std::cout << counter << std::endl;

    return 0;
}

double f(double x)
{
    return 9.81 * (68.1) * (1 - std::exp(-x * 10 / 68.1)) / x - 40;
}

template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps, int &niter)
{
    double xr = 0;
    int iter = 1;
    for (;;) // while(true)
    {
        xr = (xl + xu) / 2; // Bisection
        // ¿Encontré la raíz?
        if (std::fabs(fun(xr)) < eps)
            break;
        // Actualiza los límites
        iter++;
        if (fun(xr) * fun(xl) < 0)
        {
            xu = xr;
        }
        else
        {
            xl = xr;
        }
    }
    niter = iter;
    return xr;
}

template <class fptr2>
double bisection_recursivo(double xl, double xu, fptr2 fun, double eps, int &niter)
{
    double xr = (xl + xu) / 2;
    int iter = niter;
    iter++; // Incremento en el contador

    if (std::fabs(fun(xr)) > eps) // Condición de recursividad
    {
        if (fun(xl) * fun(xr) < 0)
        {
            xu = xr;
        }
        else
        {
            xl = xr;
        }
        
        xr = bisection_recursivo(xl, xu, fun, eps, iter);
    }

    niter = iter;
    return xr;
}