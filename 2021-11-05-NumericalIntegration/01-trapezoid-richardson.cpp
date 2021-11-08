/*
Implements several integration methods
*/

#include <cmath>
#include <iostream>

// definition
using fptr = double(double);
double fun(double x);
double trapezoid(double a, double b, double h, fptr f);
template <typename typealg>
double richardson(double a, double b, double h, fptr f, typealg alg);

// main
int main(int argc, char **argv)
{
    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    const double XMIN = std::atof(argv[1]);
    const double XMAX = std::atof(argv[2]);
    const double H = std::atof(argv[3]);

    const double exact = -std::cos(XMAX) + std::cos(XMIN);
    for (double h = 1.0e-1; h >= 1.0e-8; h /= 2.0) {
        std::cout << h << "\t"
                  << std::fabs(1 - trapezoid(XMIN, XMAX, h, fun)/exact) << "\t"
                  << std::fabs(1 - richardson(XMIN, XMAX, h, fun, trapezoid)/exact) << "\n";
    }
    return 0;
}

// implementation

double fun(double x)
{
    return std::sin(x);
}

double trapezoid(double a, double b, double h, fptr f)
{
  const int n = std::floor((b - a) / h); // Warning: (b - a)/h not integer
  double result = 0.0;
  for (int ii = 1 ; ii <= n - 1 ; ++ii)
  {
      double xi = a + ii * h;
      result += f(xi);
  }
  result += 0.5 * (f(a) + f(b));
  result *= h;

  return result;
}

template <typename typealg>
double richardson(double a, double b, double h, fptr f, typealg alg)
{
    double val1 = alg(a, b, h, f);
    double val2 = alg(a, b, h/2, f);
    return (4 * val2 - val1) / 3;
}