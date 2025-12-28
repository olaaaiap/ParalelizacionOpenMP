#include <iostream>
#include <omp.h>
//
//int main()
//{
//    int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//    int b[10] = { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
//
//
//    //Solucion general para paralelizar cualquier cosa
//    #pragma omp parallel
//    {
//        int id, numero_threads, i, comienzo, fin, N = 10;
//        id = omp_get_thread_num();
//        numero_threads = omp_get_num_threads();
//
//        comienzo = id * N / numero_threads;
//        fin = (id+1) * N / numero_threads;
//
//        for (i = comienzo;i < fin;i++)
//        {
//            a[i] = a[i] + b[i];
//        }
//    }
//
//
//    std::cout << a;
//
//
//    //Solución usando el for de openmp
//    #pragma omp parallel for 
//    for (int i = 0; i < 4; i++) {
//        a[i] = a[i] + b[i];
//        std::cout << i;
//    }
//
//
//
//    /*#pragma omp parallel num_threads(10)
//    {
//    std::cout << "Hello World!\n";
//    }*/
//    return 0;
//}