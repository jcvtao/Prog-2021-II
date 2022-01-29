#include <cmath>
#include <iostream>
int main()
{
    double pi = std::acos(-1);
    double x = 1.2345;
 
    // spot check for ν == 0.5
    std::cout << "K_.5(" << x << ") = " << std::cyl_bessel_k( .5, x) << '\n'
              << "calculated via I = " << 
              (pi/2)*(std::cyl_bessel_i(-.5,x)
                     -std::cyl_bessel_i(.5,x))/std::sin(.5*pi) << '\n';
}
