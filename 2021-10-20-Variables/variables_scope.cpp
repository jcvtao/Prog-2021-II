#include <iostream>

const int a = 8;                    // Buena práctica: utilizar const

int main(void)
{
    int a = 9;
    std::cout << a << "\n";
    std::cout << &a << "\n";
    std::cout << ::a << "\n";       // Utilizar variable global
    std::cout << &::a << "\n";

    {
        int a = 10;                 // Variable local
        std::cout << a << "\n";
        std::cout << &a << "\n";
    }

    std::cout << a << "\n";
    std::cout << &a << "\n";

    return 0;
}