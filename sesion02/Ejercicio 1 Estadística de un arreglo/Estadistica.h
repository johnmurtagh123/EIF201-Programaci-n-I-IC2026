#pragma once

using namespace std;

void leerArreglo(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Ingrese numero " << i + 1 << ": ";
        cin >> arr[i];
    }

}

int valorMayor(int arr[], int size) {
    int mayor = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > mayor)
            mayor = arr[i];
    }
    return mayor;
}

int valorMenor(int arr[], int size) {
    int menor = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < menor)
            menor = arr[i];
    }
    return menor;
}

int suma(int arr[], int size) {
    int s = 0;
    for (int i = 0; i < size; i++) {
        s += arr[i];
    }
    return s;
}

double promedio(int arr[], int size) {
    return (double)suma(arr, size) / size;
}