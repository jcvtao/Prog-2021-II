// summing :
// \sum_{n = 1}^{2N} (-1)^{n} \frac{n}{n+1}

#include <iostream>
#include <cmath>
using namespace std;

typedef double REAL;
//typedef float REAL;

REAL sum1(const int N);
REAL sum2(const int N);
REAL sum3(const int N); // supposed to be exact


int main(void)
{
  int N;

   cout.precision(16);
   for (N = 1; N <= 10000000; N += 100000) {
     cout << N << "\t" << fabs((sum1(N) - sum3(N))/sum3(N)) << endl;
  }

  return 0;
}

REAL sum1(const int N)
{
  REAL result = 0;
  double sign = -1;

  for (int i = 1; i <= 2*N; i++) {
    result = result + sign*i/(i+1);
    sign = -1*sign; // better way for changing the sign
  }

  return result;
}

REAL sum2(const int N)
{
  REAL result1 = 0, result2 = 0;
  int i;

  // possible optimization: store 2i in a tmp var.
  for (i = 1; i <= N; i++) {
    result1 = result1 + (2.0*i - 1.0)/(2.0*i);
  }

  // possible optimization: store 2i in a tmp var.
  for (i = 1; i <= N; i++) {
    result2 = result2 + 2.0*i/(2.0*i + 1.0);
  }

  return result2 - result1;
}

REAL sum3(const int N)
{
  REAL result = 0;

  // possible optimization: store 2i in a tmp var.
  for (int i = 1; i <= N; i++) {
    result = result + 1.0/(2*i*(2*i + 1));
  }

  return result;
}
