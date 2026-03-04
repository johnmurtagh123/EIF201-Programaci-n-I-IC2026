// Ejercicio 3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include "matriz.h"

int main()
{
    int matriz[FILAS][COLS];

    cout << "Ingreso de datos de la matriz " << FILAS << "x" << COLS << endl;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; i < COLS; i++) {
            cout << "  Fila " << (i + 1) << ", Columna " << (j + 1) << ": ";
            cin >> matriz[i][j];
        }
        cout << "\n";
    }
    

    imprimirMatriz(matriz);
    calcularSumaFilas(matriz);
    calcularSumaColumnas(matriz);
    calcularSumaDiagonal( matriz);


}

