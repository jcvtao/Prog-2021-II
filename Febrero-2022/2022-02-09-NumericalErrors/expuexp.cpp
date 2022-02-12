#include <iostream>
#include <cmath>
using namespace std;

//typedef double REAL;
typedef float REAL;

REAL expo1(REAL x, int N); // return e^{-x} computed with N terms
REAL expo2(REAL x, int N); // return e^{x} computed with N terms

int main(void)
{
  int Nlim;
  REAL x = 2;

  cout.precision(16);

  for (Nlim = 1; Nlim <= 36; Nlim += 1) {
    cout << Nlim;
    //cout << "\t" << fabs(exp(-x) - expo1(x, Nlim));///exp(-x);
    //cout << "\t" << fabs(exp(-x) - (1.0/expo2(x, Nlim)))/exp(-x);
    cout << "\t" << fabs(expo1(x, Nlim) - expo1(x, Nlim*2));///exp(-x);
    cout << endl;
  }

  return 0;
}

REAL expo1(REAL x, int N)
{
  REAL result = 1, powx = x;
  int sign = -1;
  int ifact = 1;

  for (int i = 1; i <= N; i++) {
    result += sign*powx/ifact;
    sign *= -1; // to change the sign
    ifact *= (i+1); // to compute ifactorial
    powx *= x; // to compute x^n
  }

  return result;
}

REAL expo2(REAL x, int N)
{
  REAL result = 1, powx = x;
  int ifact = 1;

  for (int i = 1; i <= N; i++) {
    result += powx/ifact;
    ifact *= (i+1); // to compute ifactorial
    powx *= x; // to compute x^n
  }

  return result;
}
