#include <iostream>

int main(void)
{
  const int N = 1025000;
  double data[N] = {0};
  std::cout << data << std::endl;
  std::cout << &data[0] << std::endl;
  //std::cout << data[N/2] << std::endl;

  return 0;
}
