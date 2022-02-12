#include <iostream>
#include <cmath>

int factorial(int n);
double fnaive(double x, int N);
double fsmart(double x, int N);

int main(void)
{
  std::cout.precision(16); std::cout.setf(std::ios::scientific);
  double x = 1.234534534;
  for (int NMAX = 0; NMAX <= 100; ++NMAX) {
    std::cout << NMAX
              << "\t" << fsmart(x, NMAX)
              << "\t" << std::fabs(fsmart(x, NMAX) - std::exp(-x))/std::exp(-x)
              << std::endl;
  }
  return 0;
}

double fnaive(double x, int N)
{
  double term = 0, suma = 0;
  for(int k = 0; k <= N; ++k){
    term = std::pow(-x, k)/factorial(k);
    suma += term;
  }
  return suma;
}

int factorial(int n)
{
  if (n <= 0) return 1;
  return n*factorial(n-1);
}

double fsmart(double x, int N)
{
  double term = 1, suma = 1;
  for(int k = 0; k < N; ++k){
    term *= (-x)/(k+1);
    suma += term;
  }
  return suma;
}
