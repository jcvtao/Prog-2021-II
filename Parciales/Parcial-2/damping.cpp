#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double f(double x, double m, double g, double t, double vf);
template <class fptr>
double newton(double x0, fptr fun, double eps, int &niter);

void explore_masses(void);
void explore_times(void);

int main(int argc, char *argv[])
{
    explore_masses();
    explore_times();

    return 0;
}

double f(double x, double m, double g, double t, double vf)
{
    return g * m * (1 - std::exp(-x * t / m)) / x - vf;
}

// xi+1 = xi - f(xi)/f'(xi)
template <class fptr>
double newton(double x0, fptr fun, double eps, int &niter)
{
    double h = 0.001;
    double xr = x0;
    int iter = 1;
    while (std::fabs(fun(xr)) > eps)
    {
        double fderiv = (fun(xr + h / 2) - fun(xr - h / 2)) / h;
        xr = xr - fun(xr) / fderiv;
        iter++;
    }
    niter = iter;
    return xr;
}

void explore_masses(void)
{
    int nsteps = 0;
    std::vector<double> masses{5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    std::ofstream fout("data_masses.txt");
    fout.precision(15);
    fout.setf(std::ios::scientific);
    for (auto m : masses)
    { /* g, t, vf */
        auto faux = [m](double x)
        { return f(x, m, 9.81, 10, 40); }; // lambda function captures m but exposes only one parameter x = c
        double root = newton(10, faux, 1.0e-4, nsteps);
        fout << m << "\t" << root << std::endl;
    }
    fout.close();
}

void explore_times(void)
{
    int nsteps = 0;
    std::vector<double> times{5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::ofstream fout("data_times.txt");
    fout.precision(15);
    fout.setf(std::ios::scientific);
    for (auto t : times)
    { /* g, m, vf */
        auto faux = [t](double x)
        { return f(x, 60, 9.81, t, 40); }; // lambda function | m = 70
        double root = newton(10, faux, 1.0e-4, nsteps);
        fout << t << "\t" << root << std::endl;
    }
    fout.close();
}