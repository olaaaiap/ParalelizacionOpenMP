#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <climits>
#include <algorithm>
#include <fstream>
#include <cctype>
#include "ejercicios.h"

using namespace std;



/// @brief Lee la entrada del usuario para un entero entre 1 y numMax.
/// 
/// @return el valor elegido por el usuario.
int leetInputEntero(int numMax) {
	int x;
	while (true) {
		if (cin >> x) {
			if (x >= 1 && x <= numMax) {
				return x;
			}
		}
		cout << "Opcion no valida, elige otra: ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


int main() {
	int ejercicio = -1;
	cout << "ELIGE EL EJERCICIO A EJECUTAR: \n";
	cout << "1.- Grupo 1 Ejercicio 1: Paralelizar el codigo del enunciado. \n";
	cout << "2.- Grupo 1 Ejercicio 2: Calcular la media de los valores de una matriz. \n";
	cout << "3.- Grupo 1 Ejercicio 3: Obtener una aproximacion numerica del valor de pi usando la regla del trapecio. \n";
	cout << "4.- Grupo 1 Ejercicio 6: Simular el juego de la vida. \n";
	cout << "5.- Grupo 2 Ejercicio 8: Calcular la media, valor maximo y minimo, valor con mayor frecuencia, valores mayores que 50, la matriz ordenada y la matriz traspuesta desde una matriz aleatoria. \n";
	
	
	ejercicio = leetInputEntero(5);
	
	if (ejercicio == 1) {
		ejercicio1();  
	}
	else if (ejercicio == 2) {
		ejercicio2();
	}
	else if (ejercicio == 3) {
		ejercicio3();
	}
	else if (ejercicio == 4) {
		ejercicio6();
	}
	else if (ejercicio == 5) {
		ejercicio8();
	}


	return 0;
}