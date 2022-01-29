#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

// constants
const double W = 3.1237;

typedef std::vector<double> state_t; // alias for state type

void initial_conditions(state_t & y);
void print(const state_t & y, double time);
void fderiv(const state_t & y, state_t & dydt, double t);
template <class deriv_t, class system_t, class printer_t>
void integrate_euler(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer);
template <class deriv_t, class system_t, class printer_t>
void integrate_rk4(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer);


int main(void)
{
  const double DT = 0.01;
  const double TF = 4*2*M_PI/W;
  const int N = 2;

  state_t y(N);
  initial_conditions(y);
  //integrate_euler(fderiv, y, 0.0, TF, DT, print);
  integrate_rk4(fderiv, y, 0.0, TF, DT, print);

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

template <class deriv_t, class system_t, class printer_t>
void integrate_rk4(deriv_t deriv, system_t & y, double tinit, double tend, double dt, printer_t writer)
{
  int N = y.size();
  system_t dydt(N, 0.0);
  system_t k1(N), k2(N), k3(N), k4(N), aux(N);

  double time = 0;
  int nsteps = (tend - tinit)/dt;
  for(int ii = 0; ii < nsteps; ++ii) {
    time = 0.0 + ii*dt;
    // k1
    deriv(y, dydt, time);
    for(int ii = 0; ii < N; ++ii) {
      k1[ii] = dt*dydt[ii];
    }
    // k2 aux
    for(int ii = 0; ii < N; ++ii) {
      aux[ii] = y[ii] + k1[ii]/2;
    }
    //k2
    deriv(aux, dydt, time + dt/2);
    for(int ii = 0; ii < N; ++ii) {
      k2[ii] = dt*dydt[ii];
    }
    // k3 aux
    for(int ii = 0; ii < N; ++ii) {
      aux[ii] = y[ii] + k2[ii]/2;
    }
    //k3
    deriv(aux, dydt, time + dt/2);
    for(int ii = 0; ii < N; ++ii) {
      k3[ii] = dt*dydt[ii];
    }
    // k4 aux
    for(int ii = 0; ii < N; ++ii) {
      aux[ii] = y[ii] + k3[ii];
    }
    //k4
    deriv(aux, dydt, time + dt);
    for(int ii = 0; ii < N; ++ii) {
      k4[ii] = dt*dydt[ii];
    }

    // write new data
    for(int ii = 0; ii < N; ++ii) {
      y[ii] = y[ii] + (k1[ii] + 2*k2[ii] + 2*k3[ii] + k4[ii])/6.0;
    }

    print(y, time);
  }
}
