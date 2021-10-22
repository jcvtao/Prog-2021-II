#include <iostream>

int main()
{
    std::cout << ((5==5) && (3>6)) << std::endl;
    std::cout << ((5==5) || (3>6)) << std::endl;

    int flag = (5<4) ? -1 : 32;     // Ternary operator (?) [if/else]
    std::cout << flag << std::endl;

    int m = 2, n = 17, k = 0;
    // m = 00010 , n = 10001, k = 00000
    
    k = m & n;
    std::cout << k << std::endl;
    // 00010 & 10001 = 00000 => 0

    k = m | n;
    std::cout << k << std::endl;
    // 00010 | 10001 = 10011 => 19

    k = m << 2;
    std::cout << k << std::endl;
    // 00010 << 2 = 01000 => 8

    k = m >> 2;
    std::cout << k << std::endl;
    // 00010 >> 2 = 00000 => 0

    /* Operando con bits
     * 4 = 0100, 8 = 1000               (Código binario)
     * 4&8 = 0100&1000 = 0000 = 0       (0 = false, 1 = true)
     * 4|8 = 0100|1000 = 1100 = 12
    */

    return 0;
}