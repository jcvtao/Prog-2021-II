#include <iostream>
#include <cstdlib>
#include <random>

void fill(double * ptr, int size);
double average(const double * ptr, int size);

int main(int argc, char **argv)
{
    int N = 0;
    N = std::atoi(argv[1]);

    double * data = new double [N]{0.0};

    fill(data, N);

    std::cout << average(data, N) << std::endl;

    // release memory
    delete [] data;
    data = nullptr;
    
    return 0;
}

void fill(double * ptr, int size)
{ // do not touch the random number code
    std::mt19937 gen(size); // use size as seed
    std::uniform_real_distribution<> dis(-2.0, 3.0);
    for(int ii = 0; ii < size; ++ii){
        ptr[ii] = dis(gen);
    }
}

double average(const double * ptr, int size)
{
    double suma = 0;
    for(int ii = 0; ii < size; ++ii) {
        suma += ptr[ii];
    }
    return suma/size;
}
