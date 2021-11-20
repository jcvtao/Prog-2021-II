// Computing dot product
#include <iostream>

double dotproduct(const double a1[], const double a2[], int size); // by reference by default
void init(double a1[], double a2[], int size); // by reference by default
void print(const double array[], int size);

int main(int argc, char **argv)
{
    // double x1 = 9.87, y1 = -0.65, z1 = 7.65432;
    // double x2 = -5.432, y2 = -0.6598876, z2 = -0.64359;
    //std::cout << x1*x2 + y1*y2 + z1*z2 << std::endl;

    // memoria = stack(estatico) + heap(dinamica)

    // primitive arrays //limited by stack size
    int N = 10000;
    double v1[N]{9.87, -0.65, 7.65432}, v2[N]{-5.432, -0.6598876, -0.64359};
    init(v1, v2, N);
    std::cout << dotproduct(v1, v2, N) << std::endl;
    print(v1, 10);
    print(v2, 11);

    return 0;
}

double dotproduct(const double a1[], const double a2[], int size)
{
    double dot = 0;
    for (int ii = 0; ii < size; ii++) {
        dot += a1[ii]*a2[ii];
    }
    return dot;
}
void init(double a1[], double a2[], int size)
{
    for (int ii = 0; ii < size; ii++) {
        a1[ii] = 2*ii;
        a2[ii] = 1.0/(2*ii*ii + 1);
    }
}

void print(const double array[], int size)
{
    for (int ii = 0; ii < size; ii++) {
        std::cout << array[ii] << " " ;
    }
    std::cout << "\n";
}
