      #include <iostream>
      #include <cstdlib>
      #include <vector>
      #include <random>
      #include <cmath>
   
      double trace(const std::vector<double> & data);
   
      int main(int argc, char *argv[])
      {
        // read command line parameters
        const int N = std::atoi(argv[1]);
   
        // setup random generator to fill the vector
        std::mt19937 gen(0);
        std::normal_distribution<double> dis(0.0, 1.0); // mu, sigma
   
        // declare and fill the array
        std::vector<double> arr(N*N);
        for (auto & x : arr) {
          x = dis(gen);
        }
   
        // call the pnorm function
        std::cout << trace(arr) << std::endl;
   
        return 0;
      }
   double trace(const std::vector<double> & data)
   {
     // fill here
   }
