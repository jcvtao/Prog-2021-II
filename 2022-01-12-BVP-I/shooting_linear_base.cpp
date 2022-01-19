#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>

// constants
const double H = 0.05;
const double TINF = 200;
const double T0 = 300;
const double TF = 400;
const double X0 = 0;
const double XF = 10.0;
const double DX = 0.01;

typedef std::vector<double> state_t; // alias for state type

void print(const state_t & y, double time);
void fderiv(const state_t & y, state_t & dydt, double t);

int main(void)
{
  const int N = 2;

  state_t y(N); // (T, z)
  double zi1 = 10, zi2 = 20;
  double Tf1 = 0, Tf2 = 0;
  
  // solve the problem for some z1, get final value
  y[0] = T0; y[1] = zi1;
  boost::numeric::odeint::integrate(fderiv, y, X0, XF, DX);
  Tf1 = y[0];

  // solve the problem for some z2, get final value
  y[0] = T0; y[1] = zi2;
  boost::numeric::odeint::integrate(fderiv, y, X0, XF, DX);
  Tf2 = y[0];

  // interpolate to obtain the actual initial value
  const double Z0 = zi1 + (zi2 - zi1)*(TF - Tf1)/(Tf2 - Tf1);

  // print final data
  y[0] = T0; y[1] = Z0;
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
  dydt[1] = H*(y[0] - TINF);
}
