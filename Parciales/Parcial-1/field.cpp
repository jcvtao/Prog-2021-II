#include <cstdlib>
#include <iostream>
#include <cmath>
   
using fptr = double(double);
double potential(double x);
double dev_central(double x, double h, fptr fun);
template <typename algptr>
double dev_richardson(double x, double h, fptr fun, algptr algo);


int main(int argc, char **argv)
{
  std::cout.precision(16); std::cout.setf(std::ios::scientific);

  const double h = std::atof(argv[1]);

  for(double x = 0.0; x <= 2.5; x += h) {
      std::cout << x << "\t"                                               // Valor de x
                << -(2*std::sin(x) + 2*x*std::cos(x)) << "\t"              // Valor exacto
                << - dev_richardson(x, h, potential, dev_central) << "\n"; // Valor numérico
  }

  return 0;
}


double potential(double x)
{
  return 2 * x * std::sin(x);
}

double dev_central(double x, double h, fptr fun)
{
  return (fun(x + h) - fun(x - h)) / (2 * h);
}

template <typename algptr>
double dev_richardson(double x, double h, fptr fun, algptr algo)
{
  double val1 = algo(x, h, fun);
  double val2 = algo(x, h/2, fun);

  return (4*val2 - val1)/3;
}