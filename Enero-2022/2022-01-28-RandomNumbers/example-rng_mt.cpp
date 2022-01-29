#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <vector>

int main(int argc, char **argv)
{
    const int SEED = std::atoi(argv[1]);;
    const int SAMPLES = std::atoi(argv[2]);
    //const double A = -2.0;
    //const double B = 2.0;
    const double A = 0.0;
    const double B = 2.0;
    const double XMIN = -5.0;
    const double XMAX = 5.0;
    const int NBINS = 40;
    const double DX = (XMAX-XMIN)/NBINS;

    std::vector<double> histo(NBINS, 0.0);
    std::mt19937 gen(SEED);
    //std::uniform_real_distribution<double> dist(A, B);
    std::normal_distribution<double> dist(A, B);
    std::ofstream fout("data.txt");
    for (int ii = 0; ii < SAMPLES; ++ii) {
        double r = dist(gen);
        fout << r << "\n";
        int bin = int((r - XMIN)/DX);
        if (0 <= bin && bin < NBINS) {
            histo[bin]++;
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
