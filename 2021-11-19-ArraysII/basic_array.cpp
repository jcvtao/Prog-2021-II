// Computing dot product
#include <iostream>

int main(int argc, char **argv)
{
    // double x1 = 9.87, y1 = -0.65, z1 = 7.65432;
    // double x2 = -5.432, y2 = -0.6598876, z2 = -0.64359;
    //std::cout << x1*x2 + y1*y2 + z1*z2 << std::endl;

    // memoria = stack(estatico) + heap(dinamica)

    // primitive arrays //limited by stack size
    int N = 10000;
    double v1[N]{9.87, -0.65, 7.65432}, v2[N]{-5.432, -0.6598876, -0.64359};
    double dot = 0;
    for (int ii = 0; ii < N; ii++) {
	dot += v1[ii]*v2[ii];
    }
    std::cout << dot << std::endl;

    return 0;
}
