#include <iostream>
#include <cmath>

struct Complex
{
public:
    double x{0.0}, y{0.0};
    void print(void);
    double real(void);
    double imag(void);
    double norm(void);
    double arg(void);
    Complex operator+(const Complex &rhs);
    Complex operator-(const Complex &rhs);
    Complex sin(void);
};

int main(void)
{
    Complex z1, z2, z3;
    z1.x = 4.32;
    z1.y = 5.87;
    z2.x = 3.0009;
    z2.y = -2.65;
    z1.print();
    std::cout << "z1 real : " << z1.real() << std::endl;
    std::cout << "z1 imag : " << z1.imag() << std::endl;
    std::cout << "z1 norm : " << z1.norm() << std::endl;
    std::cout << "z1 arg  : " << z1.arg() << std::endl;
    z1.print();
    z2.print();
    std::cout << "z3 = z1 + z2  : " << std::endl;
    z3 = z1 + z2;
    z3.print();
    std::cout << "z3 = z1 - z2  : " << std::endl;
    z3 = z1 - z2;
    z3.print();
    std::cout << "z3 = z1.sin() : " << std::endl;
    z3 = z1.sin();
    z3.print();

    return 0;
}

void Complex::print(void)
{
    std::cout << "(" << x << " , " << y << ")" << std::endl;
}

double Complex::real(void)
{
    return x;
}

double Complex::imag(void)
{
    return y;
}

double Complex::norm(void)
{
    return std::hypot(x, y);
}

double Complex::arg(void)
{
    return std::atan2(y, x);
}

Complex Complex::operator+(const Complex &rhs)
{
    Complex tmp;
    tmp.x = x + rhs.x;
    tmp.y = y + rhs.y;
    return tmp;
}

Complex Complex::operator-(const Complex &rhs)
{
    Complex tmp;
    tmp.x = x - rhs.x;
    tmp.y = y - rhs.y;
    return tmp;
}

Complex Complex::sin(void)
{
    Complex tmp;
    tmp.x = std::sin(x) * std::cosh(y);
    tmp.y = std::cos(x) * std::sinh(y);
    return tmp;
}