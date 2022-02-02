#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <vector>

double rho(double x);

int main(int argc, char **argv)
{
    /* # Comentario
     * Como queremos ver la 'pdf' de la función \rho(x) para x \in (-1.0 , 1.0), entonces
     * el programa se debe ejecutar con: "./a.out <SEED> 1000000 -1.0 1.0 <NBINS>"
     * donde los valores de los parámetros <SEED> y <NBINS> son de preferencia personal.
     * 
     * Para generar la figura adjunta en Moodle se utilizó: "./a.out 1 1000000 -1.0 1.0 40", y se
     * graficó en gnuplot utilizando "plot 'density.txt' w lp lw 2 pt 4 t 'probability density function'".
    */

    // Parámetros
    const int SEED = std::atoi(argv[1]);
    const int SAMPLES = std::atoi(argv[2]); // 1000000
    const double XMIN = std::atof(argv[3]); // -1.0
    const double XMAX = std::atof(argv[4]); // 1.0
    const int NBINS = std::atoi(argv[5]);
    const double DX = (XMAX - XMIN) / NBINS;

    // Límites eje y (cotas)
    const double YMIN = 0.0; // rho(x)_{min} = 0.0    x \in (-1.0,1.0)
    const double YMAX = 1.0; // rho(x)_{max} = 0.75   x \in \mathbb{R} [utilizamos 1.0]

    // 'Random distributions'
    std::mt19937 gen(SEED);
    std::uniform_real_distribution<double> X_dist(XMIN, XMAX); // Distribución uniforme eje x
    std::uniform_real_distribution<double> Y_dist(YMIN, YMAX); // Distribución uniforme eje y

    // Escribir "datos.txt"
    std::ofstream fout("datos.txt");
    std::vector<double> histo(NBINS, 0.0);
    int accepted = 0;          // Cantidad de números de aceptados [contador]
    while (accepted < SAMPLES) // (accepted < 1000000)
    {
        double x = X_dist(gen); // Coordenada en x
        double y = Y_dist(gen); // Coordenada en y
        // 'Rejection method'
        if (y < rho(x))
        {
            fout << x << "\t" << y << "\n";
            // Actualizar histograma
            int bin = int((x - XMIN) / DX);
            if (0 <= bin && bin < NBINS)
            {
                histo[bin]++;
            }

            accepted++; // Aumentar contador de números aceptados
        }
    }
    fout.close();

    // Escribir "density.txt"
    fout.open("density.txt");
    for (int ii = 0; ii < NBINS; ii++)
    {
        fout << XMIN + ii*DX << "\t" << histo[ii] / (DX*SAMPLES) << "\n";
    }
    fout.close();

    return 0;
}

double rho(double x)
{
    return (3.0 / 4.0) * (1.0 - std::pow(x, 2)); // x \in (-1,1)
}