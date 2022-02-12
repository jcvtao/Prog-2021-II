#include <cstdio>

int main(void)
{
  float x = -1.5e38, y = 1.5e38, z = 1;
  printf("%16.6f\t%16.6f\n", x + (y+z), (x+y) + z);
  printf("%16.16f\n", 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1);

  return 0;
}
