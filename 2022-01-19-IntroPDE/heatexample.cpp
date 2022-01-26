#include <iostream>
#include <vector>
#include <cmath>

const double X0 = 0.0;
const double XF = 10.0;
const double DX = 0.9;
const double DTIME = 0.1;
const double TIMEF = 24.0;
const int NSTEPS = std::lrint(TIMEF/DTIME);
const int NPRINT = NSTEPS/6;
const double K = 0.835;
const double LAMBDA = K*DTIME/(DX*DX);
const int N = std::lrint((XF-X0)/DX);
const double T0 = 100.0;
const double TF = 50.0;

void print(const std::vector<double> & v);

int main(int argc, char **argv)
{
  std::vector<double> T(N);
  std::fill(T.begin(), T.end(), 0.0);
  T[0] = T0; T[N-1] = TF;
  print(T);

  // time evolution
  for(int nstep = 0; nstep < NSTEPS; ++nstep) {
    for(int ii = 1; ii < N-1; ii++) {
      T[ii] = T[ii] + LAMBDA*(T[ii+1] - 2*T[ii] + T[ii-1]);
    }
    if (nstep%NPRINT == 0) {
      print(T);
    }
  }

  return 0;
}

void print(const std::vector<double> & v)
{
  for(int ii = 0; ii < v.size(); ++ii) {
    std::cout << X0 + ii*DX << "\t" << v[ii] << "\n";
  }
  std::cout << "\n\n";
}
