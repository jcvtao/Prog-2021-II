#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>

// constants
const double W = 3.1237;

typedef std::vector<double> state_t; // alias for state type

void initial_conditions(state_t & y);
void print(const state_t & y, double time);
void fderiv(const state_t & y, state_t & dydt, double t);

int main(void)
{
  const double DT = 0.01;
  const double TF = 4*2*M_PI/W;
  const int N = 2;

  state_t y(N);
  initial_conditions(y);
  boost::numeric::odeint::integrate(fderiv, y, 0.0, TF, DT, print);

  return 0;
}

void initial_conditions(state_t & y)
{
  y[0] = 0.9876;
  y[1] = 0.0;
}

void print(const state_t & y, double time)
{
  std::cout << time << "\t" << y[0] << "\t" << y[1] << std::endl;
}

void fderiv(const state_t & y, state_t & dydt, double t)
{
  dydt[0] = y[1];
  dydt[1] = -W*W*y[0];
}
