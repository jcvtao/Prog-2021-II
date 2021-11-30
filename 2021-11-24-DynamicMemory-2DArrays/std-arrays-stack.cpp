#include <iostream>
#include <array>

int main(void)
{
  const int N = 2500000;
  std::array<int, N> data {0};
  //std::cout << data << std::endl;
  std::cout << &data[0] << std::endl;
  //std::cout << data[N/2] << std::endl;

  return 0;
}
