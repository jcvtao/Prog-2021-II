#include <iostream>
#include <cstdlib>

void printsum(int nmax);

int main(int argc, char *argv[])
{
  const int NMAX = std::atoi(argv[1]);

  printsum(NMAX);

  return 0;
}

void printsum(int nmax)
{
  std::cout.precision(15); std::cout.setf(std::ios::scientific);
  for (int ii = 1 ; ii <= nmax ; ++ii)
  {
    double sum = 0.0;
    for (int jj = 1 ; jj <= ii ; ++jj)
    {
      sum += 1.0/(jj*jj);
    }

    std::cout << ii << "\t" << sum << "\n";
  }
}