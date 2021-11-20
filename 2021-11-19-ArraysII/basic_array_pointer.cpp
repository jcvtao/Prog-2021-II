// Computing dot product
#include <iostream>

int main(int argc, char **argv) {
  // double x1 = 9.87, y1 = -0.65, z1 = 7.65432;
  // double x2 = -5.432, y2 = -0.6598876, z2 = -0.64359;
  // std::cout << x1*x2 + y1*y2 + z1*z2 << std::endl;

  // memoria = stack(estatico) + heap(dinamica)

  // primitive arrays //limited by stack size
  int N = 10000;
  double v1[N]{9.87, -0.65, 7.65432};
  double *ptr = nullptr;
  ptr = &v1[0];
  std::cout << v1[0] << std::endl;
  std::cout << &v1[0] << std::endl;
  std::cout << &v1[1] << std::endl;
  std::cout << ptr << std::endl;
  std::cout << ptr[0] << std::endl;
  std::cout << ptr[1] << std::endl;
  std::cout << *(ptr + 2) << std::endl;

  return 0;
}
