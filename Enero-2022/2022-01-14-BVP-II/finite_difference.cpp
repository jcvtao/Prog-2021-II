//https://eigen.tuxfamily.org/dox-devel/group__TutorialSparse.html
#include <iostream>
#include <eigen3/Eigen/Dense>

const double L = 10; // Longitud de la barra
const double H = 0.01;
const double TA = 20; // TINF
const double T0 = 40;
const double TL = 200;
const int NINT = 400;
const int N = NINT + 2;
const double DX = L/(N-1); // T0 T1 T2 T3 T4
const double ALPHA = 2 + H*DX*DX;
const double BETA = H*DX*DX*TA;

int main(int argc, char **argv)
{
    Eigen::MatrixXd M(NINT, NINT);
    Eigen::VectorXd b(NINT);
    M.setZero();
    b.setZero();

    // -T_{i-1} + \alpha*T_i - T_{i+1} = \beta
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

    // M*x = b
    Eigen::VectorXd T = M.colPivHouseholderQr().solve(b);
    //std::cout << "The solution is:\n" << T << std::endl;
    //std::cout << T0 << "\n" << T << "\n" << TL << std::endl;
    std::cout << 0 << "\t" << T0 << std::endl;
    for(int ii = 0; ii < NINT; ++ii) {
      double xval = 0 + (ii+1)*DX;
      std::cout << xval << "\t" << T(ii) << std::endl;
    }
    std::cout << L << "\t" << TL << std::endl;

    return 0;
}
