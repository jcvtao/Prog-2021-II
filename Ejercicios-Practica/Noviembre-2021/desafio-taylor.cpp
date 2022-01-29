/* Escriba un programa en c++ que imprima los datos de sinx en función del número de términos
 * en la expansión en serie de Taylor. Para esto, su programa deberá leer dos números de la
 * línea de comando: x (un double) y N (un entero), donde el último es el número máximo de
 * términos a probar en la serie de Taylor. Su programa debe ir variando el número de términos
 * en la serie (hasta llegar a N) e ir impriendo el número actual de términos, el valor de la
 * expansión, y el valor de la diferencia porcentual entre la expansión y la función estandar
 * matemática std::sin(x) evaluada en el mismo x. Grafique ese error en función del número de
 * términos. Puede probar con cualquier valor de x y N, pero para poder comparar con los demás
 * estudiantes use x=1.2π y N=10. Su programa debería recibir estos argumentos desde la línea
 * de comandos. Es su funcón periódica?
*/

#include <iostream>
#include <cmath>

// Declarations
double f(double x);
double taylor_sen(double x, int N);
int factorial(int n);

int main(int argc, char **argv)
{
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);
    const double x = std::atof(argv[1]);
    const int N = std::atoi(argv[2]);
   
   // N , taylor_sen(x,n) , error_porcentual
   double exact = f(x);
   for (int ii = 1 ; ii <= N ; ii += 1)
   {
       std::cout << ii << "\t"
                 << taylor_sen(x, ii) << "\t"
                 << std::fabs(1 - taylor_sen(x, ii)/exact) << "\t"
                 << f(x) << "\n";
   }

    return 0;
}

// Definitions
double f(double x)
{
    return std::sin(x);
}

double taylor_sen(double x, int N)
{
    double result = 0.0;
    
    bool bneg = false;
    int mult = 1;

    for (int jj = 1 ; jj <= N ; jj += 2)
    {
        if(bneg)
        {
            mult = -1;
            bneg = false;
        }
        else
        {
            mult = 1;
            bneg = true;
        }

        double dev = std::pow(x , jj);
        int fac = factorial(jj);

        double term = mult * dev / fac;
        result += term;
    }

    return result;
}

int factorial(int n)
{
    int factorial = 1;
    for(int kk = 1; kk <= n ; ++kk)
    {
        factorial *= kk;
    }

    return factorial;
}