#include <iostream>
#include <cstdlib>

typedef float REAL;

int main(int argc, char **argv)
{
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  int N = std::atoi(argv[1]);
  REAL under = 1.0, over = 1.0;
  for (int ii = 0; ii < N; ++ii){
    under /= 2.0;
    over *= 2.0;
    std::cout << ii << "\t"
              << under << "\t"
              << over << "\n";
  }
  return 0;
}
