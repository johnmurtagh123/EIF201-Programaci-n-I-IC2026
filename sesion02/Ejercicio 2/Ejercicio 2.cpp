// Ejercicio 2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Inversion.h"

using namespace std;
int main()
{
    const int SIZE = 20;
    int arr[SIZE];
    int invertida[SIZE];

    for (int i = 0; i < SIZE; i++) {
        cout << "Ingrese numero " << i + 1 << ": ";
        cin >> arr[i];
    }

    invertirVector(arr, SIZE, invertida);

    for (int i = 0; i < SIZE; i++) {
        cout << invertida[i] << "\n";
    }
}

