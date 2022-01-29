#include <iostream>

int main()
{
    float var_float;
    std::cout << "Variable float #1:\n" << var_float << "\n\n";
    
    bool var_bool = false;
    std::cout << "Variable bool:\n" << var_bool << "\n\n";
    
    double var_double;
    std::cout << "Variable double, dirección:\t" << &var_double << "\n";
    std::cout << "Variable double, bytes:\t\t" << sizeof(var_double) << "\n\n";

    float var_float2 = 1.0e40;
    std::cout << "Variable float #2:\n" << var_float2 << "\n";
    // Se imprime el valor "inf", que quiere decir infinito.
    // Creo que se debe a que el valor de la variable (1.0e40 = 10^{40}) es muy grande para
    // que el computador lo pueda representar y, por lo tanto, se imprime el valor de infinito.

    return 0;
}
