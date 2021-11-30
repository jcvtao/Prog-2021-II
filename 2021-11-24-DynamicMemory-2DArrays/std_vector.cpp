// g++ -g -fsanitize=address
#include <iostream>
#include <vector>

int main(void)
{
    const int N = 5;
    //double data[N] {0};
    std::vector<double> data;
    //data.reserve(15); //affects capacity
    data.resize(N); // real size

    std::cout << "size: " << data.size() << std::endl;
    std::cout << "capacity: " << data.capacity() << std::endl;
    std::cout << "max_size: " << data.max_size() << std::endl;

    //std::cout << data[-1] << std::endl; // detected by sanitizers address

// initialize the array with even numbers
    int ii = 0;
    for(auto & x : data){
        x = 2*ii;
        ++ii;
    }

// print the array
    for(auto x : data){
        std::cout << x << std::endl;
    }

// compute mean
    double sum = 0.0;
    for(auto x : data){
        sum += x;
    }
    std::cout << "Average = " << sum/data.size() << std::endl;

    data.push_back(200.0987); // size == 6 // size == 6, capacity == 10
    data.push_back(300.0987); // size == 7 // size == 7
    data.push_back(400.0987); // size == 8 // size == 8
    std::cout << "size: " << data.size() << std::endl;
    std::cout << "capacity: " << data.capacity() << std::endl;

    return 0;
}
