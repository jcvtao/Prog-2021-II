#include <iostream>
#include <vector>
#include <cmath>

// constants
const double DELTA = 0.05;
const double LX = 1.479;            // Longitud x (Lx)
const double LY = 1.4*LX;           // Longitud y (Ly)
const int NX = int(LX/DELTA)+1;     // No. de puntos x
const int NY = int(LY/DELTA)+1;     // No. de puntos y
const int STEPS = 200;

// Constantes ubicación placas (No. de puntos x e y)
const int N_LX_3 = int((LX/3)/DELTA)+1;         // x = Lx/3        (Placa 1)
const int N_2LX_3 = int((2*LX/3)/DELTA)+1;      // x = 2*Lx/3      (Placa 2)
const int N_LY_4 = int((LY/4)/DELTA)+1;         // y = Ly/4        (1ra esquina y)
const int N_LY_F = int((LY/4 + LY/2)/DELTA)+1;  // y = Ly/4 + Ly/2 (2da esquina -> longitud y = Ly/2)

typedef std::vector<double> Matrix; // alias

void initial_conditions(Matrix & m);
void boundary_conditions(Matrix & m);
void evolve(Matrix & m);
void print(const Matrix & m);
void init_gnuplot(void);
void plot_gnuplot(const Matrix & m);

int main(void)
{
  Matrix data(NX*NY);
  initial_conditions(data);
  boundary_conditions(data);

  init_gnuplot();
  for (int istep = 0; istep < STEPS; ++istep) {
    evolve(data);
    plot_gnuplot(data);
  }

  return 0;
}
void initial_conditions(Matrix & m)
{
  for(int ii=0; ii<NX; ++ii) {
    for(int jj=0; jj<NY; ++jj) {
      m[ii*NX + jj] = 1.0;
    }
  }
}
void boundary_conditions(Matrix & m)
{
  int ii = 0, jj = 0;

  ii = 0;
  for (jj = 0; jj < NY; ++jj)
    m[ii*NX + jj] = 100;

  ii = NX-1;
  for (jj = 0; jj < NY; ++jj)
    m[ii*NX + jj] = 0;

  jj = 0;
  for (ii = 1; ii < NX-1; ++ii)
    m[ii*NX + jj] = 0;

  jj = NY-1;
  for (ii = 1; ii < NX-1; ++ii)
    m[ii*NX + jj] = 0;

  // Placa 1 (+75V)
  ii = N_LX_3;                           // x = Lx/3
  for (jj = N_LY_4; jj < N_LY_F; ++jj)   // Ly/4 <= y <= (Ly/4 + Ly/2)
    m[ii*NX + jj] = 75;

  // Placa 2 (-75V)
  ii = N_2LX_3;                          // x = 2*Lx/3
  for (jj = N_LY_4; jj < N_LY_F; ++jj)   // Ly/4 <= y <= (Ly/4 + Ly/2)
    m[ii*NX + jj] = -75;
}

void evolve(Matrix & m)
{
  for(int ii=0; ii<NX; ++ii) {
    for(int jj=0; jj<NY; ++jj) {
      // check if boundary
      if(ii == 0) continue;
      if(ii == NX-1) continue;
      if(jj == 0) continue;
      if(jj == NY-1) continue;
      if (ii == N_LX_3 && jj >= N_LY_4 && jj < N_LY_F) continue;  // Placa 1
      if (ii == N_2LX_3 && jj >= N_LY_4 && jj < N_LY_F) continue;  // Placa 2
      // evolve non boundary
      m[ii*NX+jj] = (m[(ii+1)*NX + jj] +
                    m[(ii-1)*NX + jj] +
                    m[ii*NX + jj + 1] +
                    m[ii*NX + jj - 1] )/4.0;
    }
  }
}

void print(const Matrix & m)
{
  for(int ii=0; ii<NX; ++ii) {
    for(int jj=0; jj<NY; ++jj) {
      std::cout << ii*DELTA << " " << jj*DELTA << " " <<  m[ii*NX + jj] << "\n";
    }
    std::cout << "\n";
  }  
}

void init_gnuplot(void)
{
  std::cout << "set contour " << std::endl;
  std::cout << "set terminal gif animate " << std::endl;
  std::cout << "set out 'anim.gif' " << std::endl;
}

void plot_gnuplot(const Matrix & m)
{
  std::cout << "splot '-' w pm3d " << std::endl;
  print(m);
  std::cout << "e" << std::endl;
}