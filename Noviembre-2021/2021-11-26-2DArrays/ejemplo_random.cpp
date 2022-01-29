#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include <fstream>

int main(int argc, char **argv) {
    // read parameters from command line
    const int N = std::atoi(argv[1]);
    const int SEED = std::atoi(argv[2]);
    const int A = std::atof(argv[3]);
    const int B = std::atof(argv[4]);
    const int BINS = 15;
    std::vector<double> histo(BINS, 0.0);

    // generate N random numbers with weibull distro
    //  cummuate them to compute a histogram
    std::mt19937 gen(SEED);
    std::weibull_distribution<double> d(A, B);
    const double XMIN = 0;
    const double XMAX = 2;
    const double DX = (XMAX-XMIN)/BINS;
    for (int isample = 0; isample < N; ++isample) {
        double x = d(gen);
        int boxid = int((x - XMIN)/DX);
        if(0 <= boxid && boxid < BINS)
            histo[boxid]++;
    }

    // Print the histogram to a file
    std::ofstream fout("histo.txt");
    for (int ibin = 0; ibin < BINS; ++ibin) {
        double x = XMIN + ibin*DX;
        fout << x << "\t" << histo[ibin] << "\n";
    }
    fout.close();

    return 0;
}
