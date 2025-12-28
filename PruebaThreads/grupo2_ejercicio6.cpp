#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <Windows.h>
#include <omp.h>
#include "ejercicios.h"

using namespace std;


void ejercicio6() {
	srand(time(nullptr));

	unsigned int cols, filas;
	cout << "Introduce el numero de columnas: "; cin >> cols;
	cout << "Introduce el numero de filas: "; cin >> filas;


	double tiempoSec, tiempoPar2, tiempoPar4, tiempoPar8, tiempoPar16;
	vector<vector<int>> MatrizActual(filas, vector<int>(cols));
	vector<vector<int>> MatrizSiguiente(filas, vector<int>(cols));


	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < cols; j++) {
			MatrizActual[i][j] = rand() % 2;
			MatrizSiguiente[i][j] = 0;
		}
	}



	tiempoSec = omp_get_wtime();
	int cantIteraciones = 10;
	for (int iter = 0; iter < cantIteraciones; iter++) {


		if (filas <= 40 || cols <= 40) {
			for (int i = 0; i < filas; i++) {
				for (int j = 0; j < cols; j++) {
					cout << (MatrizActual[i][j] ? " *" : "  ");
				}
				cout << '\n';
			}
		}


		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < cols; j++) {

				int neighbours = 0;


				if (i > 0) {
					neighbours += MatrizActual[i - 1][j];
					if (j > 0) {
						neighbours += MatrizActual[i - 1][j - 1];
					}
					if (j < cols - 1) {
						neighbours += MatrizActual[i - 1][j + 1];
					}
				}

				if (j > 0) {
					neighbours += MatrizActual[i][j - 1];
					if (i < filas - 1) {
						neighbours += MatrizActual[i + 1][j - 1];
					}
				}

				if (i < filas - 1) {
					neighbours += MatrizActual[i + 1][j];
					if (j < cols - 1) {
						neighbours += MatrizActual[i + 1][j + 1];
					}
				}


				if (j < cols - 1)
					neighbours += MatrizActual[i][j + 1];




				
				if (MatrizActual[i][j] == 1) {
					if (neighbours < 2 || neighbours > 3)
						MatrizSiguiente[i][j] = 0;
					else
						MatrizSiguiente[i][j] = 1;
				}
				else {
					if (neighbours == 3)
						MatrizSiguiente[i][j] = 1;
					else
						MatrizSiguiente[i][j] = 0;
				}

			}
		}
		swap(MatrizActual, MatrizSiguiente);

		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	tiempoSec = omp_get_wtime() - tiempoSec;





	int nums_threads[] = { 2, 4, 8, 16 };
	for (int num_threads : nums_threads) {
		if (num_threads == 2) tiempoPar2 = omp_get_wtime();
		else if (num_threads == 4) tiempoPar4 = omp_get_wtime();
		else if (num_threads == 8) tiempoPar8 = omp_get_wtime();
		else if (num_threads == 16) tiempoPar16 = omp_get_wtime();

		for (int iter = 0; iter < cantIteraciones; iter++) {


			if (filas <= 40 || cols <= 40) {
				for (int i = 0; i < filas; i++) {
					for (int j = 0; j < cols; j++) {
						cout << (MatrizActual[i][j] ? " *" : "  ");
					}
					cout << '\n';
				}
			}

#pragma omp parallel for collapse(2) num_threads(num_threads)
			for (int i = 0; i < filas; i++) {
				for (int j = 0; j < cols; j++) {

					int neighbours = 0;


					if (i > 0) {
						neighbours += MatrizActual[i - 1][j];
						if (j > 0) {
							neighbours += MatrizActual[i - 1][j - 1];
						}
						if (j < cols - 1) {
							neighbours += MatrizActual[i - 1][j + 1];
						}
					}

					if (j > 0) {
						neighbours += MatrizActual[i][j - 1];
						if (i < filas - 1) {
							neighbours += MatrizActual[i + 1][j - 1];
						}
					}

					if (i < filas - 1) {
						neighbours += MatrizActual[i + 1][j];
						if (j < cols - 1) {
							neighbours += MatrizActual[i + 1][j + 1];
						}
					}


					if (j < cols - 1)
						neighbours += MatrizActual[i][j + 1];
					

					if (MatrizActual[i][j] == 1) {
						if (neighbours < 2 || neighbours > 3)
							MatrizSiguiente[i][j] = 0;
						else
							MatrizSiguiente[i][j] = 1;
					}
					else {

						if (neighbours == 3)
							MatrizSiguiente[i][j] = 1;
						else
							MatrizSiguiente[i][j] = 0;
					}

				}
			}
			swap(MatrizActual, MatrizSiguiente);

			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}


		if (num_threads == 2) tiempoPar2 = omp_get_wtime()- tiempoPar2;
		else if (num_threads == 4) tiempoPar4 = omp_get_wtime()- tiempoPar4;
		else if (num_threads == 8) tiempoPar8 = omp_get_wtime()- tiempoPar8;
		else if (num_threads == 16) tiempoPar16 = omp_get_wtime()- tiempoPar16;


	}



	cout << "\n--- SECUENCIAL ---\n";

	cout << "\n | Tiempo: " << tiempoSec << "\n\n\n";


	cout << "\n--- PARALELO ---\n";
	cout << "Hilos: 2 "
		<< "\n | Tiempo: " << tiempoPar2
		<< "\n | Diferencia con secuencial (tSec - tPar): " << tiempoSec - tiempoPar2 << endl;


	cout << "\nHilos: 4 "
		<< "\n | Tiempo: " << tiempoPar4
		<< "\n | Diferencia con secuencial (tSec - tPar): " << tiempoSec - tiempoPar4 << endl;

	cout << "\nHilos: 8 "
		<< "\n | Tiempo: " << tiempoPar8
		<< "\n | Diferencia con secuencial (tSec - tPar): " << tiempoSec - tiempoPar8 << endl;

	cout << "\nHilos: 16 "
		<< "\n | Tiempo: " << tiempoPar16
		<< "\n | Diferencia con secuencial (tSec - tPar): " << tiempoSec - tiempoPar16 << endl;

}