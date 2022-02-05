#include <iostream>
#include <fstream>
#include <random>
//#include <cstdlib>
#include <vector>

double f(double x) {
    return 3.0*(1-x*x)/4.0;
}

int main(int argc, char **argv)
{
    const int SEED = std::atoi(argv[1]);;
    const int SAMPLES = std::atoi(argv[2]);
    const double XMIN = -2.0;
    const double XMAX = 2.0;
    const int NBINS = 50;
    const double DX = (XMAX-XMIN)/NBINS;

    std::vector<double> histo(NBINS, 0.0);
    std::mt19937 gen(SEED);
    std::uniform_real_distribution<double> xu(-1, 1);
    std::uniform_real_distribution<double> yu(0, 3.0/4.0);
    std::ofstream fout("data.txt");
    for (int ii = 0; ii < SAMPLES; ++ii) {
        double x = xu(gen);
        double y = yu(gen);
        if (y < f(x)) {
            fout << x << "\n";
            int bin = int((x - XMIN)/DX);
            if (0 <= bin && bin < NBINS) {
                histo[bin]++;
            }
        }
    }
    fout.close();

    fout.open("histo.txt");
    for (int ii = 0; ii < NBINS; ii++) {
        fout << XMIN + ii*DX << "\t" << histo[ii]/(DX*SAMPLES) << "\n";
    }
    fout.close();

    return 0;
}
