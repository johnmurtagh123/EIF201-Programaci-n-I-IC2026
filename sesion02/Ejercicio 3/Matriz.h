#pragma once
const int FILAS = 3;
const int COLS = 3;

using namespace std;


void imprimirMatriz(const int matriz[FILAS][COLS]) {
    cout << " Matriz ingresada ";
    for (int i = 0; i < FILAS; i++) {
        cout << "  [";
        for (int j = 0; j < COLS; j++) {
            cout << setw(5) << matriz[i][j];
        }
        cout << "  ]\n";
    }
    cout << "\n";
}

int calcularSumaFilas(const int matriz[FILAS][COLS]) {
    int resultado = 0;
    cout << " Suma por filas ";
    for (int i = 0; i < FILAS; i++) {
        int suma = 0;
        for (int j = 0; j < COLS; j++) {
            suma += matriz[i][j];
            resultado+= suma;
        }
        cout << "  Fila " << (i + 1) << ": " << setw(6) << suma << "\n";

    }
    cout << "\n";
    return resultado;
}

int calcularSumaColumnas(const int matriz[FILAS][COLS]) {
    int resultadoColumnas = 0;
    cout << "Suma por columnas ";
    for (int j = 0; j < COLS; j++) {
        int suma = 0;
        for (int i = 0; i < FILAS; i++) {
            suma += matriz[i][j];
            resultadoColumnas+= suma;
        }
        cout << "  Columna " << (j + 1) << ": " << setw(4) << suma << "\n";
    }
    cout << "\n";
    return resultadoColumnas;
}

int calcularSumaDiagonal(const int matriz[FILAS][COLS]) {
    int resultadoDiagonal = 0;
    int suma = 0;
    for (int i = 0; i < FILAS; i++) {
        suma += matriz[i][i];
        resultadoDiagonal += suma;
    }
    cout << " Suma diagonal principal ";
    cout << "  Diagonal (esquina superior-izquierda a inferior-derecha): "
        << setw(4) << suma << "\n\n";
    cout << "\n";
    return resultadoDiagonal;
}