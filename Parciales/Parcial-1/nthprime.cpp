#include <iostream>
#include <cstdlib>
#include <cmath>

int isprime(int m);
int nthprime(int n);

int main(int argc, char *argv[])
{
  const int n = std::atoi(argv[1]);
  std::cout << nthprime(n) << "\n";

  return 0;
}

int isprime(int m)
{
  int prime_yn = 1;     // Prime yes/no
  for (int jj = 2 ; jj <= std::sqrt(m) ; ++jj)
  {
    if (m % jj == 0)
    {
      prime_yn = 0;
      break;
    }
  }

  return prime_yn;
}

int nthprime(int n)
{
  int nth_prime = 0;
  int pcounter = 0;   // Primes counter
  for (int ii = 2 ; pcounter < n ; ++ii)
  {
    if (isprime(ii) == 1)
    {
      nth_prime = ii;
      pcounter += 1;
    }
  }
  
  return nth_prime;
}