#include <iostream>

// Vector3D struct
struct Vector3D
{
    double x{}, y{}, z{};

    Vector3D() {x = 0.0; y = 0.0; z = 0.0;} // Constructor
    ~Vector3D() {} // Destructor
    void print(void) {std::cout << "(" << x << " , " << y << " , " << z << ")" << std::endl;} // Print
    
    //Operator Overloading
    Vector3D operator+(const Vector3D &R) { // Suma
        Vector3D C;
        C.x = x + R.x;
        C.y = y + R.y;
        C.z = z + R.z;
        return C;
    }
    double operator*(const Vector3D &R) { // Producto punto
        return x*R.x + y*R.y + z*R.z;
    }
};


int main()
{
    Vector3D A, B, C;
    A.x = 1.0; A.y = 2.0; A.z = 3.0;
    B.x = 4.0; B.y = 5.0; B.z = 6.0;
    
    C = A + B;
    double dotProduct = A * B;
    
    C.print();
    std::cout << dotProduct << std::endl;

    return 0;
}
