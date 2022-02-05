#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <vector>

const double SQRT3 = std::sqrt(3);

double f(double x) {
    if (-1 <= x && x <= 0) return SQRT3*x + SQRT3;
    else if (0 < x && x <= 1) return -SQRT3*x + SQRT3;
    else return 0;
}

int main(int argc, char **argv)
{
    const int SEED = std::atoi(argv[1]);;
    const int SAMPLES = std::atoi(argv[2]);

    std::mt19937 gen(SEED);
    std::uniform_real_distribution<double> xu(-1, 1);
    std::uniform_real_distribution<double> yu(0, SQRT3);
    std::ofstream fout("data.txt");
    int samples = 0;
    int counter = 0;
    while (samples < SAMPLES) {
        double x = xu(gen);
        double y = yu(gen);
        if (y < f(x)) {
            fout << x << "\t" << y << "\n";
            samples++;
        }
        counter++;
    }
    fout.close();
    std::cout << "Actual tries: " << counter << "\n";

    return 0;
}
