// Calcular los números pares entre 1 y 100

// Incluir la libreria iostream (incluye las 28840 lineas al compilar)
#include <iostream>

void print_even(int nmin, int nmax); // Declaración
void print_odd(int nmin, int nmax);

// Función principal
int main(void)
{
  const int m = 1; // No se podrá cambiar después
  const int n = 15;

  print_even(m, n);
  print_odd(m, n);
  print_even(m/2, 2*n);
  print_odd(m/2, 2*n);
  
  return 0;
}

void print_even(int nmin, int nmax) // Implementación
{
  int counter = 0;
  std::cout << "Números pares entre " << nmin << " y " << nmax << ":\n";
  for (int ii = nmin ; ii <= nmax ; ii++) {
    // Si el número es par, entonces imprimir
    if (ii % 2 == 0) {
      std::cout << ii << " ";
      counter++;
    }   
  }
  std::cout << "\n";
  std::cout << "Cantidad números pares: " << counter << "\n\n";
}

void print_odd(int nmin, int nmax)
{
  int counter = 0;
  std::cout << "Números impares entre " << nmin << " y " << nmax << ":\n";
  for (int ii = nmin ; ii <= nmax ; ii++) {
    // Si el número es impar, entonces imprimir
    if (ii % 2 != 0) {
      std::cout << ii << " ";
      counter++;
    }
  }
  std::cout << "\n";
  std::cout << "Cantidad números pares: " << counter << "\n\n";
}
