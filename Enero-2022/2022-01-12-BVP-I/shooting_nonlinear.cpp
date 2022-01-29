#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>

// constants
const double H = 0.05;
const double SIGMA = 2.7e-10;
const double TINF = 200;
const double T0 = 300;
const double TF = 400;
const double X0 = 0;
const double XF = 10.0;
const double DX = 0.01;

typedef std::vector<double> state_t; // alias for state type

void print(const state_t & y, double time);
void fderiv(const state_t & y, state_t & dydt, double t);
template <class fptr>
double newton(double x0, fptr fun, double eps, int & niter);

int main(void)
{
  const int N = 2;

  state_t y(N); // (T, z)
  double zi1 = 10, zi2 = 20;
  double Tf1 = 0, Tf2 = 0;

  // create lambda function: receives one arg (z) and return the final T value minus the expected one.
  auto faux = [&y](double z){
    y[0] = T0; y[1] = z;
    boost::numeric::odeint::integrate(fderiv, y, X0, XF, DX);
    return y[0] - TF;};

  // perform a Newton-Raphson procedure to find the root
  // compute numerically the derivative
  int nsteps = 0;
  double z0  = newton(-10, faux, 0.001, nsteps);

  // print final data
  y[0] = T0; y[1] = z0;
  boost::numeric::odeint::integrate(fderiv, y, X0, XF, DX, print);

  return 0;
}

void print(const state_t & y, double time)
{
  std::cout << time << "\t" << y[0] << "\t" << y[1] << std::endl;
}

void fderiv(const state_t & y, state_t & dydt, double t)
{
  // vector is : y = (y0, y1) = (T, z)
  dydt[0] = y[1];
  dydt[1] = H*(y[0] - TINF) + SIGMA*(std::pow(y[0], 4) - std::pow(TINF, 4));
}

// xi+1 = xi - f(xi)/f'(xi)
template <class fptr>
double newton(double x0, fptr fun, double eps, int & niter)
{
  double h = 0.00001;
  double xr = x0;
  int iter = 1;
  while(std::fabs(fun(xr)) > eps) {
    double fderiv =  (fun(xr+h/2) - fun(xr-h/2))/h;
    xr = xr - fun(xr)/fderiv;
    iter++;
  }
  niter = iter;
  return xr;
}
