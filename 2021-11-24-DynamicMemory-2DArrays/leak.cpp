#include <iostream>

void leaking(int N);

int main(int argc, char *argv[]) {
    int size = 10000000;
    int reps = 1000;

    for(int ii = 0 ; ii < reps; ++ii) {
        leaking(size);
        if (reps%100 == 0) {
            std::cout << "Press enter\n";
            std::cin.get();
        }
    }

    return 0;
}

void leaking(int N){
    double *localptr = new double [N]{0};
    localptr[N/2] = 0.98;
    // no delete?
}
