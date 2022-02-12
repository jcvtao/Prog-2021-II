// substractive cancellation in cuadratic equation

#include <iostream>
#include <cmath>
using namespace std;

//typedef double REAL;
typedef float REAL;

void roots1(REAL a, REAL b, REAL c, REAL & answer1, REAL & answer2);
void roots2(REAL a, REAL b, REAL c, REAL & answer1, REAL & answer2);

int main(void)
{
  cout.precision(15);

  REAL A = 1.0;
  REAL B = 1.0;
  REAL C;
  
  for (int i = 1; i < 10; i++) {
    C = pow(10.0, -i);
    REAL ans1, ans2;
    
    roots1(A, B, C, ans1, ans2);
    cout << ans1 << "\t" << ans2 << endl;
    
    roots2(A, B, C, ans1, ans2);
    cout << ans1 << "\t" << ans2 << endl;
    
    cout << endl;
  }
  
  return 0;
}

void roots1(REAL a, REAL b, REAL c, REAL & answer1, REAL & answer2)
{
  REAL aux1 = sqrt(b*b - 4*a*c);
  REAL aux2 = 1.0/(2.0*a);
  
  answer1 = (-b + aux1)*aux2;
  answer2 = (-b - aux1)*aux2;
}

void roots2(REAL a, REAL b, REAL c, REAL & answer1, REAL & answer2)
{
  REAL aux1 = sqrt(b*b - 4*a*c);
  REAL aux2 = (-2.0*c);
  
  answer1 = aux2/(b + aux1);
  answer2 = aux2/(b - aux1);

}
