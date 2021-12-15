/* Hilbert Matrix
 * Create a function to compute the trace of that matrix. Fill the matrix as the Hilbert Matrix
 * A_{ij} = 1 / (i + j + 1)
 */

#include <iostream>

void fill(double *data, int nx, int ny);
double trace(const double *data, int nx, int ny);

int main(int argc, char *argv[])
{
    int nrows = 10;
    int ncols = 10;

    // get memory
    double *matrix = new double[nrows * ncols]{0.0};

    // fill the matrix
    fill(matrix, nrows, ncols);

    // print the matrix
    for (int ii = 0; ii < nrows; ++ii) {
        for (int jj = 0; jj < ncols; ++jj) {
            std::cout << matrix[ii * nrows + jj] << "   ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // compute and print the trace
    std::cout << trace(matrix, nrows, ncols) << std::endl;

    // release memory
    delete[] matrix;

    return 0;
}

void fill(double *data, int nx, int ny)
{
    for (int ii = 0; ii < nx; ++ii)
    {
        for (int jj = 0; jj < ny; ++jj)
        {
            double value = 1.0 / (ii + jj + 1.0);
            data[ii*nx + jj] = value;
        }
    }
}

double trace(const double *data, int nx, int ny)
{
    double sum = 0.0;
    for (int ii = 0; ii < nx; ++ii)
    {
        for (int jj = 0; jj < ny; ++jj)
        {
            if (ii == jj)
            {
                sum += data[ii * nx + jj];
            }
        }
    }
    return sum;
}