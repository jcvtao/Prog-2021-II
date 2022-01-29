#include <iostream>

int main(int argc , char **argv)
{
  //const long A = 1664525;
  //const long C = 1013904223;
  //const long M = 4294967296;
  const long A = 37;
  const long C = 0;
  const long M = 128;

  const int NTRIPLET = 100000;

  auto lcrng = [A, C, M](long x){ return (A*x + C)%M; };

  long a = 1;
  for(int inum = 0; inum < NTRIPLET; ++inum){
    a = lcrng(a); std::cout << a << " ";
    a = lcrng(a); std::cout << a << " ";
    a = lcrng(a); std::cout << a << " ";
    std::cout << "\n";
  }

  /*
  long x[3]  {lcrng(1), 0, 0};
  x[1] = lcrng(x[0]);
  x[2] = lcrng(x[1]);
  for(int inum = 0; inum < NTRIPLET; ++inum){
    long tmp = x[0];
    x[0] = x[1];
    x[1] = x[2];
    x[2] = lcrng(tmp);
    std::cout << 1.0*x[0]/(M-1) << " " << 1.0*x[1]/(M-1) << " " << 1.0*x[2]/(M-1) << "\n";
  }
*/

  return 0;
}
