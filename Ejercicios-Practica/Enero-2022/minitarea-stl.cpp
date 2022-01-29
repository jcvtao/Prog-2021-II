#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath>
#include <map>


int main(int argc, char *argv[])
{
    // 1. Generar vector de tamaño que se lee en la consola
    int N = std::atoi(argv[1]);
    std::vector<double> vec {0.0};
    vec.resize(N);
    std::iota(vec.begin(), vec.end(), 10);

    // 2. Función lambda para imprimir el vector
    std::cout << "V: ( "; std::for_each(vec.begin(), vec.end(), [](int ii){std::cout << ii << " ";}); std::cout << ")\n\n";

    // 3. Contar elementos mayores a 25
    int counter1 = std::count_if(vec.begin(), vec.end(), [](int ii){return ii > 25;});
    std::cout << "Elementos mayores a 25: " << counter1 << "\n\n";

    // 4. Contar elementos divisibles por 3 y por 5
    int counter2 = std::count_if(vec.begin(), vec.end(), [](int ii){return ii % 3 == 0 && ii % 5 == 0;});
    std::cout << "Elementos divisibles por 3 y por 5: " << counter2 << "\n\n";

    // 5. Imprimir si al menos un elementos es divisible por 7 y por 13
    if (std::any_of(vec.begin(), vec.end(), [](int ii){return ii % 7 == 0 && ii % 13 == 0;})) {
        std::cout << "Al menos un elemento es divisible por 7 y por 13" << "\n\n";
    }

    // 6. Ordenar el arreglo de mayor a menor e imprimir primeros 10 elementos
    std::sort(vec.begin(), vec.end(), [](int a, int b){return a > b;});
    std::cout << "V': ( "; std::for_each_n(vec.begin(), 10, [](int ii){std::cout << ii << " ";}); std::cout << ")\n\n";


    // 7. Calcular promedio usando accumulate, y medir el tiempo usando chrono
    auto start_time = std::chrono::steady_clock::now();
    
    auto mean = [&](double a, double b){return a + b / N;}; // Función lambda para calcular el promedio
    double avg = std::accumulate(vec.begin(), vec.end(), 0.0, mean); // Accumulate usando función lambda (mean)
    std::cout << "Promedio: " << avg << std::endl;

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    std::cout << "Tiempo en segundos: " << elapsed_seconds.count() << "s" << std::endl;


    // 8. Distribución normal, std::map, std::round
    std::ofstream fout("histo.txt");

    std::mt19937 gen(5.0); // Semilla = 5
    std::normal_distribution<> distr{5,2};

    std::map<int, int> contador{};
    for (int n = 0; n < 10000; ++n) {
        ++contador[std::round(distr(gen))];
    }
    for (auto val : contador) {
        fout << val.first << "\t" << val.second << "\n";
    }
    
    fout.close();


    return 0;
}