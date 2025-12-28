#include <iostream>
#include <omp.h>
#include <vector>
#include <stdlib.h>
#include <cstdlib> 
#include <ctime> 
#include <cmath>
#include "ejercicios.h"
#include <iomanip>

using namespace std;


void ejercicio3()
{
	cout << fixed << setprecision(10);

	unsigned int bloques;
	cout << "Introduce el numero de trapecios" << endl;
	cin >> bloques;

	double tiempoSec, tiempoPar;

	double a = 0;
	double b = 1;

	double h = (b - a) / (float)bloques;

	double resultado = 0;
	double x;
	double fx;


	cout << "\n--- SECUENCIAL ---\n";
	tiempoSec = omp_get_wtime();

	for (int i = 0; i < bloques + 1; i++) {
		x = a + i * h;
		fx = 4 / (1 + pow(x, 2));
		if (i == 0 || i == bloques) {
			resultado = resultado + fx;
		}
		else {
			resultado = resultado + (2 * fx);
		}
	}

	resultado = resultado * h / 2;

	tiempoSec = omp_get_wtime() - tiempoSec;

	cout << "\n | Tiempo: " << tiempoSec
		<< "\n | Resultado de la aproximacion: " << resultado << "\n\n\n";



	cout << "\n--- PARALELO ---\n";

	int nums_threads[] = { 2,4,8,16 };
	double resultadoP = 0;
	for (int num_threads : nums_threads) {
		resultadoP = 0;
		tiempoPar = omp_get_wtime();
#pragma omp parallel for reduction(+: resultadoP) num_threads(num_threads)
		for (int i = 0; i < bloques + 1; i++) {
			double xP = a + i * h;
			double fxP = 4 / (1 + pow(xP, 2));
			if (i == 0 || i == bloques) {
				resultadoP = resultadoP + fxP;
			}
			else {
				resultadoP = resultadoP + (2 * fxP);
			}
		}

		resultadoP = resultadoP * h / 2;
		tiempoPar = omp_get_wtime() - tiempoPar;

		cout << "Hilos: " << num_threads
			<< "\n | Tiempo: " << tiempoPar
			<< "\n | Diferencia con secuencial (tSec - tPar): " << tiempoSec - tiempoPar
			<< "\n | Resultado: " << resultadoP << endl;

	}
}