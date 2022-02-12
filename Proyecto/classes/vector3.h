#pragma once

#include <cmath>

class Vector3
{
    public:

        double a, b, c;

        Vector3(double a, double b, double c)
        {
            this->a = a;
            this->b = b;
            this->c = c;
        }

        Vector3 operator + (Vector3 &vec2)
        {
            return Vector3( (this->a + vec2.a), (this->b + vec2.b), (this->c + vec2.c) );
        }

        
        Vector3 operator - (Vector3 &vec2)
        {
            return Vector3( (this->a - vec2.a), (this->b - vec2.b), (this->c - vec2.c) );
        }

        double norm()
        {
            return std::sqrt( std::pow(this->a, 2) + std::pow(this->b, 2) + std::pow(this->c, 2));
        }

        Vector3 normalize()
        {
            double n = this->norm();
            Vector3 normalized_vector = {this->a / n, this->b / n, this->c / n};
            return normalized_vector;
        }
};

double operator * (Vector3 &vec1, Vector3 &vec2)
{
    return (vec1.a * vec2.a) + (vec1.b * vec2.b) + (vec1.c * vec2.c);
}

Vector3 operator * (double a, Vector3 vec)
{
    Vector3 result = {a*vec.a, a*vec.b, a*vec.c}; 
    return result;
}