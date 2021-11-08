/* Calcular rapidez final de la partícular aplicando teorema del trabajo - energía cinética.
 * Utilizar integración por trapecio y Simpson con 10 y 1000 intervalos.
 * Datos:   F = (2x*sin(x) , -24) N,     d = (4 , 0) m,     m = 1.25 kg
 * 
 * Sabemos que W = F * d = (2x*sin(x) * 4) + (-24 * 0) J, entonces se debe calcular
 * int_0^4(2x*sin(x)) para hallar el trabajo y posteriormente resolver el problema.
 * Veamos, utilizando el lenguaje de programación C++:
*/

#include <cmath>
#include <iostream>

// Declaración de funciones
using fptr = double(double);
double f(double x);
double trapecio(double a, double b, int n, fptr f);
double simpson(double a, double b, int n, fptr f);

int main(int argc, char **argv)
{
    // Para el ejercicio en particular se debe ejecutar el programa con ./a.out 0.0 4.0
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);
    const double XMIN = std::atof(argv[1]); // a = 0.0
    const double XMAX = std::atof(argv[2]); // b = 4.0
    const int N1 = 10;
    const int N2 = 1000;
    const double mass = 1.25;

    // Valor exacto: int(2x*sin(x)dx) = 2*sin(x) - 2x*cos(x), entonces:
    const double exact = (2 * std::sin(XMAX) - 2 * XMAX * std::cos(XMAX))
                       - (2 * std::sin(XMIN) - 2 * XMIN * std::cos(XMIN));
    
    // Diferencias porcentuales
    double DeltaTrap1 = std::fabs(1 - trapecio(XMIN, XMAX, N1, f)/exact);
    double DeltaSimp1 = std::fabs(1 - simpson(XMIN, XMAX, N1, f)/exact);
    double DeltaTrap2 = std::fabs(1 - trapecio(XMIN, XMAX, N2, f)/exact);
    double DeltaSimp2 = std::fabs(1 - simpson(XMIN, XMAX, N2, f)/exact);

    std::cout << N1 << "\t" << DeltaTrap1 << "\t" << DeltaSimp1 << "\n"
              << N2 << "\t" << DeltaTrap2 << "\t" << DeltaSimp2 << "\n";

    /* Como ya sabemos el valor aproximado (por regla de Simpson con n = 1000) de la integral, entonces
     * conocemos W. Ahora, sabemos por el Teorema del trabajo - energía cinética que W = (m*v^2)/2,
     * 
     * Luego, podemos hallar la rapidez final haciendo v = sqrt((2*W)/m)
    */
    double rapidez_final = std::sqrt((2*simpson(XMIN, XMAX, N2, f) / mass));
    // std::cout << "\nRapidez final de la partícula: " << rapidez_final << " m/s\n\n";
    // Respuesta: 2.438210483549587e+00 m/s

    return 0;
}

// Definición de funciones
double f(double x) // f(x) = 2x*sin(x)
{
    return 2 * x * std::sin(x);
}

double trapecio(double a, double b, int n, fptr f)
{
    const double h = (b - a) / n; // delta_x
    double result = 0.0;
    for (int ii = 1; ii <= n - 1; ++ii)
    {
        double xi = a + ii * h;
        result += f(xi);
    }

    result += 0.5 * (f(a) + f(b));
    result *= h;

    return result;
}

double simpson(double a, double b, int n, fptr f)
{
    const double h = (b - a) / n; // delta_x
    double result = 0.0;
    for (int ii = 1; ii <= n - 1; ++ii)
    {
        double xi = a + ii * h;

        if (ii % 2 == 0)
        {
            result += 2 * f(xi);
        }
        else
        {
            result += 4 * f(xi);
        }
    }

    result += (f(a) + f(b));
    result *= (h / 3);

    return result;
}