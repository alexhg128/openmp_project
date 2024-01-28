#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

/*
    DEFINITIONS
*/
#define N 20
#define CHUNK 5
#define OUTPUT_SIZE 20

using namespace std;

void print_arrays(float* a, float* b, float* c, float* d);


/*
    MAIN LOOP
*/
int main() {

    cout << "Sumando arreglos en paralelo" << endl;
    float a[N], b[N], c[N], d[N];
    int i;
    srand(time(NULL));

    for (i = 0; i < N; i++) {
        a[i] = i * (rand() % 10 + 1);
        b[i] =
            (i * (rand() % 10 + 1)) +
            ((0.1 + i) * (rand() % 1000 + 1) / 1000);
    }

#pragma omp parallel shared(a, b, c, d) 
    {
#pragma omp for schedule(static, CHUNK)
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
            d[i] = omp_get_thread_num();
        }
    }

    print_arrays(a, b, c, d);
}

/*
    FUNCTIONS
*/
void print_arrays(float* a, float* b, float* c, float* d) {
    cout << "Imprimiendo los primeros "
        << OUTPUT_SIZE
        << " valores de los arreglos"
        << endl << endl;

    cout << "A\t\t" << "B\t\t" << "C\t\t" << "Thread ID" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        cout << a[i] << "\t\t" << b[i] << "\t\t" << c[i] << "\t\t" << d[i] << endl;
    }

    cout << "--------------------------------------------------------------" << endl;
}