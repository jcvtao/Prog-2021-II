#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>

// === Constantes ===
const double X0 = 0;      // Límite inferior: x_i = 0
const double XF = M_PI_2; // Límite superior: x_f = pi/2
const double DX = 0.01;

// === Declaraciones ===
typedef std::vector<double> state_t; // alias for state type

void print(const state_t &y, double x);
template <class fptr>
double newton(double x0, fptr fun, double eps, int &niter);

// === Función Main ===
int main(int argc, char **argv)
{
    /* El programa recibe los tres argumentos solicitados en el enunciado del ejercicio (E0, phi0, phidot0),
     * calcula e imprime el valor de E con std::cerr, e imprime el valor de la función de onda phi(x) con std::cout.
     * Recordar la ejecución con ""./a.out E0 phi0 phidot0 1> data.txt" para obtener los resultados apropiados.
    */

    const double E0 = std::atof(argv[1]);      // Valor energía inicial
    const double phi0 = std::atof(argv[2]);    // Valor phi(0)
    const double phidot0 = std::atof(argv[3]); // Valor dphi/dx(0)

    const int N = 2;
    state_t y(N); // (T, z)

    // == Functor ==
    // Fderiv func; func.E = value;
    struct Fderiv
    {
        double E_ = 0; //internal parameter
        void operator()(const state_t &y, state_t &dydt, double t) { //external interface, is a function
            // vector is : y = (y0, y1) = (phi, z), z = dphi/dx
            dydt[0] = y[1];
            dydt[1] = -E_ * y[0];
        }
    };

    // == Función lambda ==
    // receives one arg (Energy) and return the final T value minus the expected one
    auto faux = [&y, phi0, phidot0](double E){
        y[0] = phi0;
        y[1] = phidot0;
        Fderiv j;
        j.E_ = E; // declare functor and assing internal var E  to lambda argument
        boost::numeric::odeint::integrate(j, y, X0, XF, DX);
        return y[0] - 0;};

    // Método de Newton (precisión: 1.0e-6)
    int nsteps = 0;
    double E = newton(E0, faux, 1.0e-6, nsteps); // Cálculo de E

    std::cerr << E << std::endl; // Imprimir [con cerr] valor de E

    // Imprimir [con cout] la función de onda phi(x) en el rango -pi/2 <= x <= pi/2
    Fderiv j;
    j.E_ = E;
    boost::numeric::odeint::integrate(j, y, -M_PI_2, M_PI_2, DX, print);

    /* Para generar la gráfica adjunta se utilizaron los siguientes datos iniciales para tres funciones de onda:
     * * 0.1 0 1 -> E = 4
     * * 9.1 0 1 -> E = 64
     * * 4.1 1 0 -> E = 81
     *
     * Para darle formato a la gráfica se utilizaron los siguiente comandos en gnuplot:
     * set tics pi/4; set xtics add ("π/2" 1.57079) [...]; set xrange [-1.75:1.75]; set yrange [-1.25:1.25]
    */

    return 0;
}

// === Definiciones ===
void print(const state_t &y, double x)
{ // Imprimir [con cout] phi(x)
    std::cout << x << "\t" << y[0] << "\t" << y[1] << std::endl;
}

// xi+1 = xi - f(xi)/f'(xi)
template <class fptr>
double newton(double x0, fptr fun, double eps, int &niter)
{
    double h = 0.00001;
    double xr = x0;
    int iter = 1;
    while (std::fabs(fun(xr)) > eps)
    {
        double fderiv = (fun(xr + h / 2) - fun(xr - h / 2)) / h;
        xr = xr - fun(xr) / fderiv;
        iter++;
    }
    niter = iter;
    return xr;
}