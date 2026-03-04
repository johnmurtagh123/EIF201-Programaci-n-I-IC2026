// Ejercicio 1 Estadística de un arreglo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include "Estadistica.h"

using namespace std;

int main() {
    const int SIZE = 10;
    int arr[SIZE];

    for (int i = 0; i < SIZE; i++) {
        cout << "Ingrese numero " << i + 1 << ": ";
        cin >> arr[i];
    }

    cout << "Mayor: " << valorMayor(arr, SIZE) << endl;
    cout << "Menor: " << valorMenor(arr, SIZE) << endl;
    cout << "Suma: " << suma(arr, SIZE) << endl;
    cout << "Promedio: " << promedio(arr, SIZE) << endl;

    return 0;
}