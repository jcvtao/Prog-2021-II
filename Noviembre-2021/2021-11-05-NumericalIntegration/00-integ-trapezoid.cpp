/*
Implementes several integration methods
*/

#include <cmath>
#include <iostream>

// definition
double fun(double x);
template <typename fptr>
double trapezoid(double a, double b, double h, fptr f);

// main
int main(int argc, char **argv)
{
    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    const double XMIN = std::atof(argv[1]);
    const double XMAX = std::atof(argv[2]);
    const double H = std::atof(argv[3]);

    const double exact = -std::cos(XMAX) + std::cos(XMIN);
    for (double h = 1.0e-1; h >= 1.0e-8; h /= 10.0) {
        std::cout << h << "\t"
                  << std::fabs(1 - trapezoid(XMIN, XMAX, h, fun)/exact) << "\n";
    }
    return 0;
}

// implementation

double fun(double x)
{
    return std::sin(x);
}

template <typename fptr>
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