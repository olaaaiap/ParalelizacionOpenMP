
#include <iostream>
#include <omp.h>
#include <vector>
#include <stdlib.h>
#include <cstdlib> 
#include <ctime> ¡
#include "ejercicios.h"

using namespace std;


void ejercicio2()
{
    srand(time(NULL));

    double tiempoSec;
    double tiempoPar;
    long suma = 0;

    unsigned int cols;
    unsigned int filas;
    cout << "Introduce el numero de columnas de la matriz" << endl;
    cin >> cols;
    cout << "Introduce el numero de filas de la matriz" << endl;
    cin >> filas;


    vector<vector<int>> M(filas, vector<int>(cols));
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            M[i][j] = rand() % 100;
        }
    }

    cout << "\n--- SECUENCIAL ---\n";
    tiempoSec = omp_get_wtime();
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            suma += M[i][j];
        }
    }

    double media_seq = (double)suma / (filas * cols);

    tiempoSec = omp_get_wtime() - tiempoSec;


    cout << "\n | Tiempo: " << tiempoSec
        << "\n | Media: " << media_seq << "\n\n\n";



    cout << "\n--- PARALELO ---\n";
    int nums_threads[] = {2,4,8,16};
    long sumaP = 0;
    for (int num_threads : nums_threads) {
        sumaP = 0;
        tiempoPar = omp_get_wtime();

       
    #pragma omp parallel for shared (M) reduction(+: sumaP) num_threads(num_threads)
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < cols; j++) {
                sumaP += M[i][j]; 
            }
        }

        double media_par = (double)sumaP / (filas * cols);
        tiempoPar = omp_get_wtime() - tiempoPar;

        cout << "Hilos: " << num_threads
            << "\n | Tiempo: " << tiempoPar
            << "\n | Diferencia con secuencial (tSec - tPar): " << tiempoSec - tiempoPar
            << "\n | Media: " << media_par << "\n\n\n" << endl;

    }


}