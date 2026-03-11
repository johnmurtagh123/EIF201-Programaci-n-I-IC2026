// Control de pesos paquete.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Paquetes.h"

using namespace std;

int main() {

    cout << "=== Control de Pesos de Paquetes ===" << endl;
    cout << "Empresa de Mensajeria - Registro Diario" << endl;
    cout << "======================================" << endl << endl;
    
    int cantidad = 0;
    double* pesos = crearRegistro(cantidad);

    cout << "\nIngreso de pesos:" << endl;
    ingresarPesos(pesos, cantidad);

    double total = calcularPesoTotal(pesos, cantidad);
    double promedio = total / cantidad;

    cout << "\n--- Resultados ---" << endl;
    cout << "Cantidad de paquetes : " << cantidad << endl;
    cout << "Peso total           : " << total << " kg" << endl;
    cout << "Peso promedio        : " << promedio << " kg" << endl;

    double limite = 0.0;
    cout << "\nIngrese el limite de peso permitido (kg): ";
    cin >> limite;

    int sobreLimite = contarSobreLimite(pesos, cantidad, limite);
    cout << "Paquetes que superan " << limite << " kg: " << sobreLimite << endl;

    const double* masPesado = buscarMasPesado(pesos, cantidad);
    int indiceMayor = masPesado - pesos; // aritmética de punteros
    cout << "\nPaquete mas pesado   : Paquete " << (indiceMayor + 1)
        << " con " << *masPesado << " kg" << endl;
  
    delete[] pesos;
    pesos = nullptr;

    cout << "\nMemoria liberada correctamente." << endl;
    cout << "======================================" << endl;

    return 0;
}
