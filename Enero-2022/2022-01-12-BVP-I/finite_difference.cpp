//https://eigen.tuxfamily.org/dox-devel/group__TutorialSparse.html
#include <iostream>
#include <Eigen/Dense>

const double L = 10;
const double H = 0.01;
const double TA = 20;
const double T0 = 40;
const double TL = 200;
const int NINT = 40;
const int N = NINT + 2;
const double DX = L/(N-1);
const double ALPHA = 2 + H*DX*DX;
const double BETA = H*DX*DX*TA;

int main(int argc, char **argv)
{
    Eigen::MatrixXd M(NINT, NINT);
    Eigen::VectorXd b(NINT);
    M.setZero();
    b.setZero();

    for(int ii = 0; ii < NINT; ++ii) {
        if (ii >= 1) {
            M(ii, ii-1) = -1;
        }
        M(ii, ii) = ALPHA;
        if (ii <= NINT-2) {
            M(ii, ii+1) = -1;
        }
        b(ii) = BETA;
    }
    b(0) += T0;
    b(NINT-1) += TL;

    //std::cout << M << std::endl;
    //std::cout << b << std::endl;

    Eigen::VectorXd x = M.colPivHouseholderQr().solve(b);
    //std::cout << "The solution is:\n" << x << std::endl;
    std::cout << T0 << "\n" << x << "\n" << TL << std::endl;

    return 0;
}
