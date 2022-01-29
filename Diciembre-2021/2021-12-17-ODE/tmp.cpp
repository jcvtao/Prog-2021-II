#include <iostream>
#include <numeric>
#include <valarray>

int main(void)
{
  std::valarray<double> v1(2);
  std::valarray<double> v2(2);
  double dt = 0.1;
  v1 = -0.43;
  v2 = dt*v1;
  std::cout << v1[0] << "  " << v1[1] << std::endl;
  std::cout << v2[0] << "  " << v2[1] << std::endl;

  return 0;
}
