#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

typedef std::vector<double> state_t; // alias for state type

// constants
const double W = 3.1237;

void initial_conditions(state_t & y);
void print(const state_t & y, double time);
void fderiv(const state_t & y, state_t & dydt, double t);
template <class deriv_t, class system_t, class printer_t>
void integrate_euler(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer);


int main(void)
{
  const double DT = 0.01;
  const double TF = 4*2*M_PI/W;
  const int N = 2;
  state_t y(N);
  initial_conditions(y);
  integrate_euler(fderiv, y, 0.0, TF, DT, print);

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

template <class deriv_t, class system_t, class printer_t>
void integrate_euler(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer)
{
  int N = y.size();
  system_t dydt(N, 0.0);
  double time = 0;
  int nsteps = (tend - tinit)/dt;
  for(int ii = 0; ii < nsteps; ++ii) {
	time = 0.0 + ii*dt;
    deriv(y, dydt, time);
    for (int ii = 0; ii < N; ++ii) {
      y[ii] += dt*dydt[ii];
    }
	print(y, time);
  }
}
