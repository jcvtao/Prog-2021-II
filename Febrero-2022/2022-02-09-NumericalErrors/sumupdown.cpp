#include <iostream>
#include <cmath>
using namespace std;

//typedef double REAL;
typedef float REAL;

REAL sumup(REAL N);
REAL sumdown(REAL N);

int main(void)
{
  int Nlim = 1000;
  cout.precision(16);

  for (Nlim = 1; Nlim < 1000000; Nlim += 1000) {
    // optimization: store the sums in temporal varibles
    // in order to compute each of them only once
    cout << Nlim << "\t"
      //<< sumup(Nlim) << "\t"
      //<< sumdown(Nlim) << "\t"
         << fabs((sumup(Nlim) - sumdown(Nlim))/(sumup(Nlim)))
         << endl;
  }

  return 0;
}

REAL sumup(REAL N)
{
  REAL result = 0;

  for (int n = 1; n <= N; n++)
    result += 1.0/n;

  return result;
}

REAL sumdown(REAL N)
{
  REAL result = 0;

  for (int n = N; n >= 1; n--)
    result += 1.0/n;

  return result;
}
