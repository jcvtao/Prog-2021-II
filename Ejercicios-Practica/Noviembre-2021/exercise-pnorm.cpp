#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>

double pnorm(const std::vector<double> & data, int P);

int main(int argc, char *argv[])
{
  // read command line parameters
  const int N = std::atoi(argv[1]);
  const int P = std::atoi(argv[2]);

  // setup random generator to fill the vector
  std::mt19937 gen(0);
  std::uniform_real_distribution<double> dis(1.0, 2.0);

  // declare the array
  std::vector<double> arr;
  arr.resize(N);

  // fill the array using an automatic for
  for (auto & x : arr) {
    x = dis(gen);
  }

  // call the pnorm function
  std::cout << pnorm(arr, P) << std::endl;

  std::sort(arr.begin(), arr.end());

  std::cout << arr[N/2] << std::endl;

  return 0;
}

double pnorm(const std::vector<double> & data, int P)
{
  double result = 0.0;
  for (auto & x : data) {
    result += std::pow(std::fabs(x), P);
  }
  return std::pow(result, 1.0/P);
}