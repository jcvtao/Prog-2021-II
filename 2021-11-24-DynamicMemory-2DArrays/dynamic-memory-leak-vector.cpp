#include <iostream>
#include <vector>

void leakmemory(void);

int main(int argc, char *argv[])
{
    for (int ii = 0; ii < 1000; ++ii) {
        leakmemory();
        if (ii%100 == 0) {
            std::cout << "ii: " << ii << "\n";
            std::cin.get();
        }
    }

    return 0;
}

void leakmemory(void)
{
  const int N = 15000000; // this can be read in runtime
  std::vector<double> data;
  data.reserve(N);
  //data.resize(N);

  //std::cout << ptr[N/2] << std::endl;

}
