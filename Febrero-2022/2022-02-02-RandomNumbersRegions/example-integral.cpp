#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <vector>


double f(double x, double y) {
    return std::sin(std::sqrt(std::log(x+y+1)));
}

bool inregion(double x, double y) {
    return (((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5)) <= 0.25);
}

int main(int argc, char **argv)
{
    const int SEED = std::atoi(argv[1]);;
    const int SAMPLES = std::atoi(argv[2]);

    std::mt19937 gen(SEED);
    std::uniform_real_distribution<double> xu(0, 1);
    std::uniform_real_distribution<double> yu(0, 1);
    std::ofstream fout("data.txt");
    int samples = 0;
    int counter = 0;
    double integral = 0;
    while (samples < SAMPLES) {
        double x = xu(gen);
        double y = yu(gen);
        if (inregion(x,y)) {
            fout << x << "\t" << y << "\n";
            integral += f(x, y);
            samples++;
        }
        counter++;
    }
    fout.close();
    std::cout << "Actual tries: " << counter << "\n";
    std::cout << "Integral: " << integral*M_PI/(4*samples) << "\n";
    return 0;
}
