#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <climits>
#include <algorithm>
#include <fstream>
#include <cctype>
using namespace std;
#include "ejercicios.h"


/// @brief Calcula la media de todos los valores de la matriz M.
/// 
/// @return la media.
double calcularMedia(const vector<vector<int>>& M, int num_threads) {
    long long suma = 0;

#pragma omp parallel for reduction(+:suma) num_threads(num_threads)
    for (int i = 0; i < M.size(); i++)
        for (int j = 0; j < M[i].size(); j++)
            suma += M[i][j];

    return (double)suma / (M.size() * M[0].size());
}

/// @brief Encuentra el valor máximo de la matriz M.
/// 
/// @return el valor máximo.
int maxValorPar(const vector<vector<int>>& M, int num_threads) {
    int globalMax = INT_MIN;

#pragma omp parallel num_threads(num_threads)
    {
        int localMax = INT_MIN;
#pragma omp for
        for (int i = 0; i < M.size(); i++)
            for (int j = 0; j < M[i].size(); j++)
                localMax = max(localMax, M[i][j]);

#pragma omp critical
        globalMax = max(globalMax, localMax);
    }

    return globalMax;
}

/// @brief Encuentra el valor mínimo de la matriz M.
/// 
/// @return el valor mínimo.
int minValorPar(const vector<vector<int>>& M, int num_threads) {
    int globalMin = INT_MAX;

#pragma omp parallel num_threads(num_threads)
    {
        int localMin = INT_MAX;
#pragma omp for
        for (int i = 0; i < M.size(); i++)
            for (int j = 0; j < M[i].size(); j++)
                localMin = min(localMin, M[i][j]);

#pragma omp critical
        globalMin = min(globalMin, localMin);
    }

    return globalMin;
}


/// @brief Encuentra el valor con más frecuencias en la matriz M.
/// 
/// @return el valor con más repeticiones.
int numMaxRepsPar(const vector<vector<int>>& M, int num_threads) {
    vector<int> contador(100, 0);

#pragma omp parallel num_threads(num_threads)
    {
        vector<int> localCount(100, 0);

#pragma omp for
        for (int i = 0; i < M.size(); i++)
            for (int j = 0; j < M[i].size(); j++)
                localCount[M[i][j]]++;

#pragma omp critical
        for (int v = 0; v < 100; v++)
            contador[v] += localCount[v];
    }

    int maxCantidad = 0;
    int maxValor = INT_MIN;
    for (int v = 0; v < 100; v++) {
        if (contador[v] > maxCantidad) {
            maxCantidad = contador[v];
            maxValor = v;
        }
    }

    return maxValor;
}


/// @brief Cuenta la cantidad de valores en la matriz M que son mayores que 'mayorQue'.
/// 
/// @return la cantidad de valores mayores que 'mayorQue'.
int contarMayoresQuePar(const vector<vector<int>>& M, int mayorQue, int num_threads) {
    int cantidad = 0;
#pragma omp parallel for  reduction(+:cantidad) num_threads(num_threads)
    for (int i = 0; i < M.size(); i++)
        for (int j = 0; j < M[0].size(); j++)
            if (M[i][j] > mayorQue)
                cantidad++;
    return cantidad;
}

/// @brief Ordena la matriz M de menor a mayor.
/// 
/// @return la matriz ordenada.
vector<vector<int>> ordenarMatrizPar(const vector<vector<int>>& M, int num_threads) {
    vector<vector<int>> ordenada = M; // copia de la matriz original
    vector<int> vectorM(M.size() * M[0].size());

#pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < M.size(); i++)
        for (int j = 0; j < M[0].size(); j++)
            vectorM[i * M[0].size() + j] = M[i][j];


    sort(vectorM.begin(), vectorM.end());


#pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < M.size(); i++)
        for (int j = 0; j < M[0].size(); j++)
            ordenada[i][j] = vectorM[i * M[0].size() + j];

    return ordenada;
}


/// @brief Calcula la traspuesta de la matriz M.
/// 
/// @return la matriz traspuesta.
vector<vector<int>> traspuestaPar(const vector<vector<int>>& M, int num_threads) {
    vector<vector<int>> traspuesta(M[0].size(), vector<int>(M.size()));

#pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < M.size(); i++)
        for (int j = 0; j < M[0].size(); j++)
            traspuesta[j][i] = M[i][j];

    return traspuesta;
}



void ejercicio8() {
    srand(time(nullptr));

    unsigned int cols, filas;
    cout << "Introduce el numero de columnas: "; cin >> cols;
    cout << "Introduce el numero de filas: "; cin >> filas;

    vector<vector<int>> M(filas, vector<int>(cols));
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < cols; j++)
            M[i][j] = rand() % 100;



    cout << "\n--- SECUENCIAL ---\n";

    double tiempoSec = omp_get_wtime();
    double media = calcularMedia(M, 1);
    int max = maxValorPar(M, 1);
    int min = minValorPar(M, 1);
    int maxReps = numMaxRepsPar(M, 1);
    int cantidad = contarMayoresQuePar(M, 50, 1);
    vector<vector<int>> Mordenada = ordenarMatrizPar(M, 1);
    vector<vector<int>> Mtraspuesta = traspuestaPar(M, 1);
    tiempoSec = omp_get_wtime() - tiempoSec;


    cout << "\n | Tiempo: " << tiempoSec
        << "\n | Media: " << media
        << "\n | Max: " << max
        << "\n | Min: " << min
        << "\n | Valor que mas se repite: " << maxReps
        << "\n | Cantidad de valores mayores que 50: " << cantidad
        << "\n | Matriz ordenada y traspuesta guardadas correctamente\n\n\n";

    std::ofstream archivoMordenada("matriz_ordenada.txt");
    std::ofstream archivoMtraspuesta("matriz_traspuesta.txt");

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < cols; ++j) {
            archivoMordenada << Mordenada[i][j] << ", ";
            archivoMtraspuesta << Mtraspuesta[i][j] << ", ";
        }
        archivoMordenada << "\n";
        archivoMtraspuesta << "\n";
    }

    archivoMordenada.close();
    archivoMtraspuesta.close();


    cout << "\n--- PARALELO ---\n\n";
    int nums_threads[] = { 2, 4, 8, 16 };
    for (int num_threads : nums_threads) {
        double tiempoPar = omp_get_wtime();
        double mediaP = calcularMedia(M, num_threads);
        int maxP = maxValorPar(M, num_threads);
        int minP = minValorPar(M, num_threads);
        int maxRepsP = numMaxRepsPar(M, num_threads);
        int cantidadP = contarMayoresQuePar(M, 50, num_threads);
        vector<vector<int>> MordenadaP = ordenarMatrizPar(M, num_threads);
        vector<vector<int>> MtraspuestaP = traspuestaPar(M, num_threads);

        tiempoPar = omp_get_wtime() - tiempoPar;


        cout << "Hilos: " << num_threads
        << "\n | Tiempo: " << tiempoPar
        << "\n | Diferencia con secuencial (tSec - tPar): " << tiempoSec - tiempoPar
        << "\n | Media: " << mediaP 
        << "\n | Max: " << maxP 
        << "\n | Min: " << minP
        << "\n | Valor que mas se repite: " << maxRepsP
        << "\n | Cantidad de valores mayores que 50: " << cantidadP << "\n\n\n";

       

    }

}
