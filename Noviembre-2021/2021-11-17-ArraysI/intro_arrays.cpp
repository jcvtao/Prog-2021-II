// DONE Calcular el producto punto entre dos vectores, de dimension 2
// DONE Calcular el producto punto entre dos vectores, de dimension 3
// TODO Calcular el producto punto entre dos vectores, de dimension 10

#include <iostream>

int main(int argc, char **argv)
{
    // double x1 = 9.87, y1 = -0.65, z1 = 7.65432;
    // double x2 = -5.432, y2 = -0.6598876, z2 = -0.64359;
    // std::cout << x1*x2 + y1*y2 + z1*z2 << std::endl;

    /* memoria = stack(estatico) + heap(dinamica) */

    // primitive arrays - Limited by stack size
    int N = 10;
    double v1[N]{9.87, -0.65, 7.65432}, v2[N]{-5.432, -0.6598876, -0.64359}; // Bloque de memoria
    // double dot = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    double dot = 0;
    for (int ii = 0; ii < N; ii++)
    {
        dot += v1[ii]*v2[ii];
    }
    std::cout << dot << std::endl;

    return 0;
}